#!/usr/bin/env python
# vim:fileencoding=utf-8

from __future__ import (unicode_literals, division, absolute_import,
                        print_function)

import sys
import os
import subprocess


arch = sys.argv[1][1:]
src_dir = os.environ.get('APPVEYOR_BUILD_FOLDER')
output_dir = os.path.join(src_dir, 'build')

def build_docker():
    DOCKERFILE = '''
FROM {}
MAINTAINER Doug Massay
ARG DEBIAN_FRONTEND=noninteractive
RUN useradd --home-dir=/tmp --uid=1000 --gid=100 flightcrew

# Basic build environment
RUN apt-get update && apt-get install -y software-properties-common python-software-properties build-essential python
RUN add-apt-repository ppa:george-edison55/precise-backports
RUN apt-get update && apt-get install -y cmake cmake-data
RUN apt-get clean
'''.format('ubuntu:precise' if arch == '64' else 'daald/ubuntu32:precise')
    with open(os.path.join(output_dir, 'dockerfile'), 'wb') as f:
        f.write(DOCKERFILE.encode('utf-8'))
    cmd = ('docker', 'build', '-t', ('flightcrew:' + arch), '-f', f.name, output_dir)
    print(*cmd)
    p = subprocess.Popen(cmd)
    if p.wait() != 0:
        raise SystemExit(p.wait())

build_docker()

cmd = [
    'docker', 'run',
    '-v', src_dir + ':/sources:ro',
    '-v', output_dir + ':/build:rw',
    '--tmpfs', '/tmp:rw,nodev,nosuid,size=6G,noatime,exec',
    '--rm=true',
    '--interactive=' + ('true' if sys.stdin.isatty() else 'false'),
    '--tty=' + ('true' if sys.stdin.isatty() else 'false'),
    'flightcrew:' + arch,
    'bash', '/sources/appveyor_scripts/build_flightcrew.sh',
]

print(*cmd)

raise SystemExit(subprocess.Popen(cmd).wait())