
# Online tool to create gitignore configs

https://www.toptal.com/developers/gitignore

# Problem: you move repo locally - all files now marked as having changes

```
git config core.filemode false
```

# Problem: You delete the stash

```
git fsck --unreachable | grep commit | cut -d ' ' -f3 | xargs git log --merges --no-walk


git update-ref refs/stash 4b3fc45c94caadcc87d783064624585c194f4be8 -m "My recovered stash"

or 

git update-ref refs/stash 4b3fc45c94caadcc87d783064624585c194f4be8 --create-reflog -m "My recovered stash"
```

# Problem: You accidentally deleted a branch in your Git repository.

## Resolution deleted branch

Make sure to perform all of this locally, and confirm your repo is in the state you desire before pushing to Bitbucket Cloud.
It may also be a good idea to clone your current repo, and test these solutions out first.

## If you just deleted the branch, you'll see something like this in your terminal:

Deleted branch <your-branch> (was <sha>)
To restore the branch, use: 

git checkout -b <branch> <sha>

## If you don't know the 'sha' off the top of your head, you can:

Find the 'sha' for the commit at the tip of your deleted branch using: 

```cmd
git reflog
```

To restore the branch, use: 

```cmd
git checkout -b <branch> <sha>
```

## If your commits are not in your reflog:

You can try recovering a branch by reseting your branch to the sha of the commit found using a command like: 

```cmd
git fsck --full --no-reflogs --unreachable --lost-found | grep commit | cut -d\  -f3 | xargs -n 1 git log -n 1 --pretty=oneline > .git/lost-found.txt
```

You can then display each commit using one of these: 

```cmd
git log -p <commit>
git cat-file -p <commit>
```
 # FIX slow git working on mac 

```cmd 
sudo sysctl -w net.inet.tcp.ecn_negotiate_in=0
```

#  save local workspace settings (legacy build system)

```cmd
git update-index --assume-unchanged Viber.xcworkspace/xcshareddata/WorkspaceSettings.xcsettings
```

#  build a project

```cmd

git submodule sync

git submodule update --init --recursive --force

```

* remove all from libcach/

* remove all from derived data

* remove all from components/VoiceLib-ios/ExternalVoiceLib/build/


# interactive rebasing

```cmd

git rebase -i head~3

pick -> e

git add changesFiles

git rebase --continue

```

# branching

## fdd server workflow

let's pretend you have a link to fdd server: 

```

fdd-runner-vo-inform-blocked-users.viberdev.com

```

then you should create branch named 


```

fdd-vo-inform-blocked-users

```

in server menu after activation select your branch

that's all for now.

## initial

0. create fork of upstream repo

```

Kanstantsin Bucha / Viber_iOS

```
1. add remote named |origin| which will point to your fork repo
3. add remote named |upstream| whick will point to master repo

## feature creation

|upstream| is a repo with release master branch

|origin| is a fork repo 

1. checkout head  to upstream/master

```cmd

git checkout upstream/master

```

2. pull changes to HEAD

```cmd

git pull

```

3. check status

```cmd

git status

```

4. update submodules

```cmd

git submodule update --init --recursive --force

```

5. look at HEAD in |Graphic Git Tool| head  

6. create feature branch |adjust-add-new-events-2|
> (use dashes to separate words)

```cmd

./fdd-start-feature.sh -f adjust-add-new-events-2

```

7. checkout status

```cmd

git status

```

8. create new commit |IOS-25189 Title of issue| for a feature development and push to |origin|

```cmd

git push origin head

```

9. create merge request


## workflow

0. |dev| branch could be named after part of the feature that be implemented

```
IOS-25897
```

1. Check out this new |dev| branch from a |feature| branch of |upstream|
2. Push |dev| branch -u to |origin|
```cmd
 git push -u origin HEAD
```
3. Do your work,
4. Create new merge request from fork repo |origin| |dev| branch to master repo |upstream| |feature| branch
5. Add reviewers by mention them in a new message. begin with @ and type a viber name 
```
@Sergey.Plotkin please review
```
6. wait for a review
7. After a merge pull --rebase |feature| branch
8. get gersion by ./gitver

```Obj-C
./gitver
```

> rt902-18-bugfix.2

9. Set it ready

if feature: [Ready for QA].  Assign task to QA Anna Sokolovskaya,

if bug: [Resolved]. Assign to bug reporter

set |fix revision| version by last digit number of |./gitver|

>2

add affected parts description

> affected formatted message button layout

write in comment full |.gitver|

```
fixed in rt902-18-bugfix.78
```

## fdd

### if voice lib has another version that on master - >

* check out all submodules to the target commits

* commit changes in Viber project

* check all submodules hashes twice

* clean build folder in xCode

* build  VoiceLib

* then build Viber

### fdd runner brancching name

FDD name: `fdd-runner-vo-inform-blocked-users.viberdev.com`

fdd feature server will be  `fdd-vo-inform-blocked-users`


[list of all running fdd](http://fdd-nginx-01.viberdev.com/find_runners.php)


