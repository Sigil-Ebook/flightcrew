#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals, division, absolute_import, print_function

import sys
import os
import inspect
import subprocess
from subprocess import Popen, PIPE
import stat

SCRIPT_DIR = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

target = None
xname = None

is_64bit = sys.maxsize > 2**32

if sys.platform.startswith('win'):
    target = "win32"
    if is_64bit:
        target = 'win64'
    xname = 'flightcrew-plugin.exe'
elif sys.platform.startswith('darwin'):
    target = 'osx'
    xname = 'flightcrew-plugin'
else:
    target = 'unx32'
    if is_64bit:
        target = 'unx64'
    xname = 'flightcrew-plugin'
   
# This needs to be kept in sync with FlightCrew ResultId.h
result_id_map = {
    "100" : "All ok",
    "101" : "Unable to perform validation",
    "300" : "Error generic",
    "301" : "Error schema not satisfied",
    "500" : "Error epub not valid zip archive",
    "501" : "Error epub no container xml",
    "502" : "Error epub mimetype bytes invalid",
    "700" : "Error ocf container doesnt list opf",
    "701" : "Error ocf container specified OPF doesnt exist",
    "900" : "Error XML not well formed",
    "901" : "Error XML element not present",
    "902" : "Error XML wrong element count",
    "903" : "Error XML child not recognized",
    "904" : "Error XML attribute not recognized",
    "905" : "Error XML required attribute missing",
    "906" : "Error XML id not unique",
    "907" : "Error XML bad id value",
    "908" : "Error XML specifies neither utf8 nor utf16",
    "909" : "Error XML bytestream neither utf8 nor utf16",
    "1100" : "Error OPF package not root",
    "1101" : "Error OPF idref id does not exist",
    "1102" : "Error OPF idref not unique",
    "1103" : "Error OPF bad spine toc value",
    "1104" : "Error OPF package unique identifier does not exist",
    "1105" : "Error OPF bad package version",
    "1106" : "Error OPF bad item linear value",
    "1107" : "Error OPF bad item media type value",
    "1108" : "Error OPF bad creator or contributor role value",
    "1109" : "Error OPF bad reference type value",
    "1110" : "Error OPF bad date value",
    "1111" : "Error OPF item href invalid uri",
    "1112" : "Error OPF item href has fragment",
    "1113" : "Error OPF item href not unique",
    "1114" : "Error OPF item reqmod without reqns",
    "1115" : "Error OPF item file doesnt exist",
    "1116" : "Error OPF NCX not present",
    "1117" : "Error OPF reachable ops doc not in spine",
    "1118" : "Error OPF reachable resource not in manifest",
    "1300" : "Error NCX content file does not exist",
    "1301" : "Error NCX content fragment does not exist",
    "1500" : "Error XHTML bad DTD",
    "2000" : "Warning generic",
    "2200" : "Warning OPF resource in manifest not reachable",
    "2201" : "Warning non ascii filename",
}
 
def generate_line_offsets(s):
    if s is None:
        return None
    offlst = [0]
    i = s.find('\n', 0)
    while i >= 0:
        offlst.append(i)
        i = s.find('\n', i + 1)
    return offlst

def charoffset(line, col, offlst):
    coffset = offlst[line-1]  + 1 + (col - 1)
    return coffset
     
def run(bk):

    epubversion = "2.0"
    if bk.launcher_version() >= 20160102:
        epubversion = bk.epub_version()
    if epubversion.startswith("3"):
        print("Error: FlightCrew only validates epub2 ebooks")
        return -1

    # cheat and get real path to ebook root since we will not ever write
    # anything, only read and validate
    ebook_root = bk._w.ebook_root

    # define FlightCrew command line parameters
    args = []
    exe_path = os.path.join(SCRIPT_DIR, target, xname)

    # ensure you have execute rights for unix based platforms
    if target == 'osx' or target.startswith('unx'):
        os.chmod(exe_path,0o744)

    args.append(exe_path)
    args.append(ebook_root)
    
    print("Running FlightCrew ... please wait")
    process = Popen(args, stdout=PIPE, stderr=PIPE)
    res_out, res_err = process.communicate()
    retcode = process.returncode
    
    # check if problems detected
    if len(res_err) > 0 or (retcode is not None and retcode > 0):
        
        # use quick parser to get error information
        qp = bk.qp
        qp.setContent(res_err)

        found_problem = False
        content = None
        lastfilepath = None

        for text, tprefix, tname, ttype, tattr in qp.parse_iter():
            if text is not None:
                content = text
            else:
                if tname == "problem" and ttype == 'begin':
                    content = None
                    ptype = None
                    lineno = None
                    colno = None
                    resid = None
                    msg = None
                    filepath = None
                    coffset = None
                    continue

                if tname == "type" and ttype == 'end':
                    ptype = content
                    continue

                if tname == "filepath" and ttype == 'end':
                    filepath = content
                    continue
                    
                if tname == "line" and ttype == 'end':
                    lineno = content
                    continue

                if tname == "column" and ttype == 'end':
                    colno = content      
                    continue
                    
                if tname == "resultid" and ttype == 'end':
                    resid = result_id_map[content]
                    continue

                if tname == "msg" and ttype == 'end':
                    msg = content
                    continue

                if tname == "problem" and ttype == 'end':
                    # generate file offsets once per file
                    if bk.launcher_version() >= 20160802 and filepath != lastfilepath:
                        text = None
                        afile = os.path.join(ebook_root, filepath)
                        if os.path.isfile(afile):
                            with open(afile, 'rb') as f:
                                text = f.read()
                                text = text.decode('utf-8', errors='replace')
                        offlst = generate_line_offsets(text)
                        lastfilepath = filepath
                    
                    # generate column offset
                    if bk.launcher_version() >= 20160802:
                        if lineno is not None and colno is not None and offlst is not None:
                            try:
                                nlineno = int(lineno)
                                ncolno = int(colno)
                                coffset = charoffset(nlineno, ncolno, offlst)
                            except ValueError:
                                coffset = None
                        
                    msg = resid + ' : ' +  msg + " near column " + colno
                    # since will be passed as attribute make sure to handle any embedded quotes
                    # all other entity replacements have already been done
                    msg = msg.replace("\"","&quot;")
                    if coffset:
                        bk.add_extended_result(ptype, filepath, lineno, coffset, msg)
                    else:
                        bk.add_result(ptype, filepath, lineno, msg)
                    found_problem = True
                    continue
                    
        if not found_problem:
            print(res_err);

    else :
        print(res_err)
        print(res_out)
                   
    # Setting the proper Return value is important.
    # 0 - means success
    # anything else means failure

    return 0


def main():
    print('I reached main when I should not have\n')
    return -1


if __name__ == '__main__':
    sys.exit(main())
