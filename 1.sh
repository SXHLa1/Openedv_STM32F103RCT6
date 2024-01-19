# Step 1 - ensure on master
git checkout master;

# Step 2-3 - ensure up to date
git fetch; git pull;

# Step 4 - Get Last Tag (you'll need to know it to bump to the next one)
git describe --tags $(git rev-list --tags --max-count=1)

# Step 5 - Prepend all the changes from previous tag to HEAD to the changelog
git log --pretty=format:'### **%s**%n###### %h %an - _%aD_%n%n%b%n' $(git describe --tags $(git rev-list --tags --max-count=1))...HEAD --no-merges | cat - CHANGELOG.md > temp && mv temp CHANGELOG.md;

# Step 6 - Prepend the new Release header to the changelog. Make sure to use the correct version number
echo "\n# Release v1.1.1\n" | cat - CHANGELOG.md > temp && mv temp CHANGELOG.md;

# Step 7-9 - Push the CHANGELOG.md (this happens before creating the tag)
git add --all; git commit -m "Update CHANGELOG.md to v1.1.1"; git push origin master;

# Step 10 - Get the annotated tag logs (copy this for next step. Maybe use xclip or pbcopy to make your life easier)
git log --pretty=format:'%s' $(git describe --tags $(git rev-list --tags --max-count=1))...HEAD --no-merges

# Step 11 - Create the tag with the NEXT version. Paste the output from Step 10 as the annotated text.
git tag -a v1.1.1

# Step 12 - Push tag to master
git push origin master --tags

# Step 13-14 - Checkout testing branch and make sure up to date.
git checkout testing; git pull;

# Step 15 - Fast-forward merge the tag onto testing
git merge --ff-only v1.1.1;

# Step 16 - Push to testing
git push origin testing --tags

# Step 17-18 - Checkout production branch and make sure up to date.
git checkout production; git pull;

# Step 19 - Fast-forward merge the tag onto production
git merge --ff-only v1.1.1;

# Step 20 - Push to production
git push origin production --tags