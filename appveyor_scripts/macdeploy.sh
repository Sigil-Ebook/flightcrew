#!/bin/sh

#ARCHIVE=$REPO_NAME-$FIXED_BRANCH-$(date +%Y-%m-%d_%H_%M_%S)-$COMMIT.tar.bz2
#echo "Creating archive $ARCHIVE"
#tar cfj $ARCHIVE dist
#FILESIZE=$(stat -c%s "$ARCHIVE")
#echo "Finished archive (size $FILESIZE), starting Google Drive upload"
#./bin/gdrive upload --refresh-token $GDRIVE_REFRESH_TOKEN --parent $GDRIVE_DIR "$ARCHIVE"
echo "Testing gdrive"
gdrive list --refresh-token $GDRIVE_REFRESH_TOKEN
# FILESIZE=$(stat -c%s ./bin/flightcrew-plugin)
#echo "File size = $FILESIZE"
pwd
gdrive upload --refresh-token $GDRIVE_REFRESH_TOKEN --parent $GDRIVE_DIR ./bin/flightcrew-plugin
echo "Finished Google Drive upload"
