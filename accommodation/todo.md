# Buy

- [ ] nasal spray from china
- [ ] Вим Хоф Дыхание

# Read

- [ ] <https://fuckingswiftui.com>
- [ ] Up the organisation
- [ ] Договориться можно обо всем
- [ ] Mythical man-month book
- [ ] The Hard Thing About Hard Things book
- [ ] Humanware--Practical Usability Engineering.

# Learn

- [ ] Android First App -> Clone Detecta group


# move some links in the skills section form 

<https://truudev.atlassian.net/wiki/spaces/WA/pages/2254307336/MacOS+Developer+Resources>

## learn docker if helpful

## <https://cyber-dojo.org/creator/home>

## Check C++ vector filtering

```
copy_if(assets.begin(), assets.end(), back_inserter(photos), [] (shared_ptr<MediaAsset> p) -> bool
{
    // Use dynamic_pointer_cast to test whether
    // element is a shared_ptr<Photo>.
    shared_ptr<Photo> temp = dynamic_pointer_cast<Photo>(p);
    return temp.get() != nullptr;
});
```
