
ZSH_DISABLE_COMPFIX="true"

# make VS Code default terminal editor

export EDITOR="code --wait"

# Path to your oh-my-zsh installation.

export PATH="$PATH:/Users/bucha/.cargo/bin"
export PATH="$PATH:/usr/local/bin"
export PATH="$PATH:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
export ZSH="/Users/bucha/.oh-my-zsh"
ssh-add -K

# for nvm installed through brew
export NVM_DIR="$HOME/.nvm"
source $(brew --prefix nvm)/nvm.sh

# Set name of the theme to load --- if set to "random", it will
# load a random theme each time oh-my-zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/robbyrussell/oh-my-zsh/wiki/Themes
ZSH_THEME="robbyrussell"

