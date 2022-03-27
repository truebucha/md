#Сейчас jQuery позволяет загрузить файл по ссылке одной строкой

```javascript

$.getScript("my_lovely_script.js", function(){

   alert("Script loaded but not necessarily executed.");

});

или используя такую функцию в своем коде

function loadScript(url, callback)

{

    //добавим наш скрипт файл к head динамически(это приведет к его загрузке)

    var head = document.getElementsByTagName('head')[0];

    var script = document.createElement('script');

    script.type = 'text/javascript';

    script.src = url;

    // добавляем события.

    // два события для совместимости с разными браузерами.

    script.onreadystatechange = callback;

    script.onload = callback;

    // запускаем загрузку

    head.appendChild(script);

}

Then you write the code you want to use AFTER the script is loaded in a lambda function:

var myPrettyCode = function() {

   // Here, do what ever you want

};

вот так загружаем файл с кодом

loadScript("my_lovely_script.js", myPrettyCode);

В будущем мы используем именованный exports, в стандарте от 2015 он описан

Но он еще не работает

В подключаемом модуле пишем следующее

// module "my-module.js"

export function cube(x) {

  return x * x * x;

}

const foo = Math.PI + Math.SQRT2;

export { cube, foo };

В скрипле внутри страницы

import { cube, foo } from 'my-module'; //my-module название подключенного файла 

console.log(cube(3)); // 27

console.log(foo);    // 4.555806215962888
```
