const body = document.body;
const e1 = document.createElement("p");
const e2 = document.createElement("p");
e1.innerHTML = "Мокшин Иван Николаевич 409Б-20"
body.appendChild(e1);
body.appendChild(e2);

for (let i = 6; i <= 100; i++) {
    if (i % 2 == 0) {
        e2.innerHTML += ", " + i;
    }
}

if (prompt("Вы хотите зайти на сайт?", "Да") === "Да") {
    if (confirm("Вы уверены?")) {
        alert("Добро пожаловать на сайт");
    }
}

const metatags = document.head.children;
const e3 = document.createElement("p");
document.body.appendChild(e3);
for (const tag of metatags) {
    e3.innerHTML += ", " + tag.tagName;
}

function getChainLength(element) {
    let length = 0;
    while (element.children.length) {
        length++;
        element = element.children[0];
    }
    return length;
}
metatags = document.head.children;
let maxLength = -1;
let maxElement = null;
for (let element of metatags) {
    let length = getChainLength(element);
    if (length > maxLength) {
        maxLength = length;
        maxElement = element;
    }
}
const e4 = document.createElement("p");
e4.innerHTML = maxElement.tagName;
document.body.appendChild(e4);



let divs = document.getElementsByTagName("div");

for (const div of divs) {
    div.style.color = "red";
}

const button = document.createElement("button");
button.innerHTML = "Erase all buttons";
button.onclick = () => {
    document.getElementsByTagName('button').forEach(x => {
        x.innerHTML = ""
    });
}

var lastScrollTop = 0;
document.onscroll = (evt) => {
    var scroll = document.documentElement.scrollTop;
    if (scroll > lastScrollTop) {
        document.appendChild("<p>" + new Date() + "</p>");
    }
}