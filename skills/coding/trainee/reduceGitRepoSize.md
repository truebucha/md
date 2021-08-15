### <https://docs.gitlab.com/ee/user/project/repository/reducing_the_repo_size_using_git.html>

Reduce repository size
Git repositories become larger over time. When large files are added to a Git repository:

Fetching the repository becomes slower because everyone must download the files.
They take up a large amount of storage space on the server.
Git repository storage limits can be reached.
Rewriting a repository can remove unwanted history to make the repository smaller. We recommend git filter-repo over git filter-branch and BFG.

Rewriting repository history is a destructive operation. Make sure to back up your repository before you begin. The best way back up a repository is to export the project.
Purge files from repository history
To reduce the size of your repository in GitLab, you must first remove references to large files from branches, tags, and other internal references (refs) that are automatically created by GitLab. These refs include:

refs/merge-requests/* for merge requests.
refs/pipelines/* for pipelines.
refs/environments/* for environments.
refs/keep-around/* are created as hidden refs to prevent commits referenced in the database from being removed
These refs are not automatically downloaded and hidden refs are not advertised, but we can remove these refs using a project export.

To purge files from a GitLab repository:
Install git filter-repo using a supported package manager or from source.

Generate a fresh export from the project and download it. This project export contains a backup copy of your repository and refs we can use to purge files from your repository.

Decompress the backup using tar:

tar xzf project-backup.tar.gz

This contains a project.bundle file, which was created by git bundle.

Clone a fresh copy of the repository from the bundle using --bare and --mirror options:

git clone --bare --mirror /path/to/project.bundle

Using git filter-repo, purge any files from the history of your repository. Because we are trying to remove internal refs, we rely on the commit-map produced by each run to tell us which internal refs to remove.

git filter-repo creates a new commit-map file every run, and overwrite the commit-map from the previous run. You need this file from every run. Do the next step every time you run git filter-repo.
To purge all files larger than 10M, the --strip-blobs-bigger-than option can be used:

git filter-repo --strip-blobs-bigger-than 10M

To purge specific large files by path, the --path and --invert-paths options can be combined.

git filter-repo --path path/to/big/file.m4v --invert-paths

See the git filter-repo documentation for more examples and the complete documentation.

Because cloning from a bundle file sets the origin remote to the local bundle file, delete this origin remote, and set it to the URL to your repository:

git remote remove origin
git remote add origin https://gitlab.example.com/<namespace>/<project_name>.git

Force push your changes to overwrite all branches on GitLab:

git push origin --force 'refs/heads/*'

Protected branches cause this to fail. To proceed, you must remove branch protection, push, and then re-enable protected branches.

To remove large files from tagged releases, force push your changes to all tags on GitLab:

git push origin --force 'refs/tags/*'

Protected tags cause this to fail. To proceed, you must remove tag protection, push, and then re-enable protected tags.

To prevent dead links to commits that no longer exist, push the refs/replace created by git filter-repo.

git push origin --force 'refs/replace/*'

Refer to the Git replace documentation for information on how this works.

Run a repository cleanup.

Repository cleanup
Introduced in GitLab 11.6.

Repository cleanup allows you to upload a text file of objects and GitLab removes internal Git references to these objects. You can use git filter-repo to produce a list of objects (in a commit-map file) that can be used with repository cleanup.

Introduced in GitLab 13.6, safely cleaning the repository requires it to be made read-only for the duration of the operation. This happens automatically, but submitting the cleanup request fails if any writes are ongoing, so cancel any outstanding git push operations before continuing.

To clean up a repository:

Go to the project for the repository.
Navigate to Settings > Repository.
Upload a list of objects. For example, a commit-map file created by git filter-repo which is located in the filter-repo directory.

If your commit-map file is larger than 10MB, the file can be split and uploaded piece by piece:

split -l 100000 filter-repo/commit-map filter-repo/commit-map-

Click Start cleanup.
This:

Removes any internal Git references to old commits.
Runs git gc --prune=30.minutes.ago against the repository to remove unreferenced objects. Repacking your repository temporarily causes the size of your repository to increase significantly, because the old pack files are not removed until the new pack files have been created.
Unlinks any unused LFS objects attached to your project, freeing up storage space.
Recalculates the size of your repository on disk.
GitLab sends an email notification with the recalculated repository size after the cleanup has completed.

If the repository size does not decrease, this may be caused by loose objects being kept around because they were referenced in a Git operation that happened in the last 30 minutes. Try re-running these steps after the repository has been dormant for at least 30 minutes.

When using repository cleanup, note:

Project statistics are cached. You may need to wait 5-10 minutes to see a reduction in storage utilization.
The cleanup prunes loose objects older than 30 minutes. This means objects added or referenced in the last 30 minutes are not be removed immediately. If you have access to the Gitaly server, you may slip that delay and run git gc --prune=now to prune all loose objects immediately.
This process removes some copies of the rewritten commits from the GitLab cache and database, but there are still numerous gaps in coverage and some of the copies may persist indefinitely. Clearing the instance cache may help to remove some of them, but it should not be depended on for security purposes!



### <https://stackoverflow.com/questions/2116778/reduce-git-repository-size>


 git gc --aggressive is one way to force the prune process to take place (to be sure: git gc --aggressive --prune=now). You have other commands to clean the repo too. Don't forget though, sometimes git gc alone can increase the size of the repo!

It can be also used after a filter-branch, to mark some directories to be removed from the history (with a further gain of space); see here. But that means nobody is pulling from your public repo. filter-branch can keep backup refs in .git/refs/original, so that directory can be cleaned too.

Finally, as mentioned in this comment and this question; cleaning the reflog can help:

git reflog expire --all --expire=now
git gc --prune=now --aggressive
An even more complete, and possibly dangerous, solution is to remove unused objects from a git repository
