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

function findLongestTagChain(node, currentChain = []) {
    currentChain.push(node.tagName);
    if (node.children && node.children.length > 0) {
        let longestChain = currentChain;

        for (let i = 0; i < node.children.length; i++) {
            const child = node.children[i];
            const childChain = findLongestTagChain(child, currentChain.slice());

            if (childChain.length > longestChain.length) {
                longestChain = childChain;
            }
        }

        return longestChain;
    }

    return currentChain;
}
const longestTagChain = findLongestTagChain(document.documentElement);
console.log("Length: " + longestTagChain.length);
for (const tag of longestTagChain) {
    console.log(tag);
}


let divs = document.getElementsByTagName("div");
for (const div of divs) {
    div.style.color = "red";
}

const button = document.createElement("button");
button.innerHTML = "Erase";
button.onclick = () => {
    const selected = document.querySelectorAll('.mainindent > p');
    if (button.innerHTML === "Erase") {
        button.innerHTML = "Return";
        for (const x of selected) {
            x.style.display = "none";
        }
        x.style.display = "block"
    } else {
        button.innerHTML = "Erase";
        for (const x of selected) {
            x.style.display = "block";
        }
    }

}
document.body.appendChild(button);

var lastScrollTop = 0;
document.onscroll = (evt) => {
    var scroll = document.documentElement.scrollTop;
    if (scroll > lastScrollTop) {
        const e5 = document.createElement("p");
        e5.innerHTML = new Date().toString() + " : " + (scroll - lastScrollTop);
        document.body.appendChild(e5);
    }
}

document.querySelectorAll("*").forEach(el => {
    if (el.shadowRoot) console.log(el.shadowRoot)
});
