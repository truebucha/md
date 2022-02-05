
```
git config --global core.editor "code --wait"

git config --global -e

```
then copy paste this into config

```
[diff]
    tool = default-difftool
[difftool "default-difftool"]
    cmd = code --wait --diff $LOCAL $REMOTE
```

also `export EDITOR="code --wait"`
