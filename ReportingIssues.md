# What the issue tracker is not #

**The issue tracker is not a helpdesk!** Issues that boil down to "I get this error with my file, how do I fix it" will be **closed as invalid.** The issue tracker is for reporting bugs with FlightCrew itself and for requesting new features.

If you want help in fixing problems with your epub files, we recommend [the epub subforum on MobileRead](http://www.mobileread.com/forums/forumdisplay.php?f=179). Many knowledgeable people frequent that forum (including the FlightCrew developers) who will be happy to help you with your validation problems.

But the issue tracker is **not** the place to report them!

# Searching for related issues #
So you found a bug and want to report it? Or you want to request a new feature? That’s great!

But are you sure this bug/feature request hasn’t already been reported? If it has, reporting it again does no good. You are better off starring the original report. To check whether an issue for your problem has been created, go to the [issue tracker](http://code.google.com/p/sigil/issues/list). Read through the list of open issues. See anything that could be related? If you do, click on the issue report and examine its details. If this looks like your problem, please star it. “Starring” means clicking on the star icon with the blue outline until you see it filled in with yellow. Now that issue has become more prominent, since issues with more stars are fixed/implemented sooner.

If you can’t find anything related, then change “Search: Open Issues” to “Search: All Issues” and now type in a few keywords that could locate the issue. It could already be closed with a fix awaiting release. Also take a look at the FAQ wiki page, it may have an answer.

Nothing found? Well then you need to make a new issue.

# Writing good issue reports #

Writing good issue reports is not hard. A good rule of thumb is to include **any and all** relevant information. Start by opening the ["New Issue" form](http://code.google.com/p/flightcrew/issues/entry).

## Bug reports ##
You need to write a **step-by-step** procedure that can **repeatedly reproduce the problem**. “Reproduce” means that a developer can read your issue, perform the steps you listed and see the bug immediately. “Repeatedly” means that the developer can perform this sequence as many times as necessary and the bug will always show up.

The developer needs to be able to see and experience the problem firsthand. Your description is only as good as the inverse of the amount of time it takes to experience the bug. **There is no such thing as an issue report that is _too_ detailed.** The more information you provide, the better your issue report will be.

If you are reporting a bug related to an error/warning that FlightCrew is reporting, **include an epub file in your report that will trigger this error/warning**. If you feel that the error/warning emitted should not be emitted for the epub you are attaching to the issue, **please cite the appropriate standard document that backs up your claim**. "Cite" means quote a sentence or paragraph and include a link to the document.

**Try to make the file as small as possible, don't just attach huge epub files**. Usually the error/warning is triggered by just a section of your file, so try to remove everything except that section. Then try to reproduce the problem with just this smaller file. If it still shows up, then try to make it even smaller until you are unable to reproduce it. Then attach the smallest possible file that still reproduces the problem.

If your file is under copyright (say, an e-book novel; **have you minimized the file?**), use the "Private Issue" template on the "New Issue" form. This will mark the issue as Private and only you and the FlightCrew developers will be able to see it. Other people (and search engines) will not be. Let me say that again: the **only** people that will be able to see the issue (and thus access the attached file) are the FlightCrew developers and you. It will **not** be publicly accessible in any way, shape or form.

You also need to specify what version of FlightCrew you are using. Bugs are **practically always** version related.

After you submit the issue, it will be either “Accepted” or rejected. If it’s accepted, a fix for it will be developed. This may take anywhere from a couple of hours to days or weeks (or months!). When your issue is marked as “Fixed”, please understand that the problem will be fixed in the **next** version of FlightCrew . You cannot just download the current version right after the issue is marked as “Fixed” and expect that the problem will now be gone. The **next** version of FlightCrew will have this fix, and the amount of time from the moment a fix is created to the moment a new version is released may be considerable! Have patience.

## Feature requests ##

First of all, switch the issue template to “Enhancement report from user”.

If you notice that FlightCrew is not reporting errors/warnings where other epub validators are, please report it on the tracker. We want FlightCrew to be as complete as possible.

If there's a warning or error that you think FlightCrew should raise on certain files but currently does not, you will have to provide a detailed rationale for the proposed change in behavior. If you think a new error needs to be raised, **please cite the appropriate standards document.** For warnings, more leeway is allowed. Warnings can be raised even for things that are technically valid, but go against common sense or industry best practices. You will still need to provide a detailed rationale.

As always, you need to provide a minimal epub file for which the new error/warning _should_ be raised.