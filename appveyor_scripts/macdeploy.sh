#!/bin/sh
ORIGFILENAME=flightcrew-plugin
COMMIT=$(echo $TRAVIS_COMMIT | cut -c1-7)
DTE=$(echo $(date +%Y-%m-%d_%H_%M_%S) | cut -c1-10)
NEWFILENAME="$ORIGFILENAME-$TRAVIS_BRANCH-$COMMIT-$DTE-mac"
cp "./bin/$ORIGFILENAME" "./bin/$NEWFILENAME"
FILESIZE=$(stat -f%z "./bin/$NEWFILENAME")
echo "Finished rename (size $FILESIZE), starting Google Drive upload"
gdrive --refresh-token $GDRIVE_REFRESH_TOKEN upload --parent $GDRIVE_DIR "./bin/$NEWFILENAME"
echo "Finished Google Drive upload"
