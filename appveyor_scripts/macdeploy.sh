#!/bin/sh
ORIGFILENAME=./bin/flightcrew-plugin
NEWFILENAME="$ORIGFILENAME-$TRAVIS_BRANCH-$TRAVIS_COMMIT-$(date +%Y-%m-%d_%H_%M_%S)"
cp "$ORIGFILENAME" "$NEWFILENAME"
FILESIZE=$(stat -f%z "$NEWFILENAME")
echo "Finished rename (size $FILESIZE), starting Google Drive upload"
gdrive --refresh-token $GDRIVE_REFRESH_TOKEN upload --parent $GDRIVE_DIR "$NEWFILENAME"
echo "Finished Google Drive upload"
