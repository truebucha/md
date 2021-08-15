# Workspace settings

## per user settings

Build System -> new

Derived data -> Workspace relative location | ../derived |

Issues:

* Show live issues for source code -> enabled
  
* Show issues for active scheme only

## advanced

Build location -> Unique

Full index datastore visibility -> false


## Crach without stack trace

To have both the line causing the exception highlighted (and not UIApplicationMain() in main.m) AND to see the reason for the exception (e.g., "error: A fetch request must have an entity."), do this:

In the Breakpoint navigator:

Add (+), Add Exception Breakpoint

Select the new breakpoint, Control-Click, Edit Breakpoint

Add Action

Enter: po $arg1

The relevant part of the stack trace will be in the nagivator area.

This seems to still work in Xcode 9

Here is my addition for use with Xcode 6 and below.

Enter: po (NSException*) $eax

In Xcode 6 you must explicitly provide the object type because it is no longer inferred.

# remove key binding from shortcuts

open `~/Library/Developer/Xcode/UserData/KeyBindings/`

edit personal.idekeybindings

remove

```
<key>Keyboard Shortcut</key>
<string>^&lt;</string>
```

from

```
<dict>
    <key>Action</key>
    <string>execute:</string>
    <key>Alternate</key>
    <string>NO</string>
    <key>CommandID</key>
    <string>Xcode.IDEPlaygroundEditor.CmdDefinition.Execute</string>
    <key>Group</key>
    <string>Editor Menu for Playground</string>
    <key>GroupID</key>
    <string>Xcode.IDEPegasusPlaygroundEditor.MenuDefinition.Editor</string>
    <key>GroupedAlternate</key>
    <string>NO</string>
    <key>Keyboard Shortcut</key>
    <string>^&lt;</string>
    <key>Navigation</key>
    <string>NO</string>
    <key>Title</key>
    <string>Execute Playground</string>
</dict>
```

    
