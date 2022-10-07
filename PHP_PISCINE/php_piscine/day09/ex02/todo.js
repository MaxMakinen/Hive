
var cookies = document.cookie;
if (cookies)

function remover(elem) {
    let text = "Are you sure you want to remove task?";
    if (confirm(text)) {
        elem.parentNode.removeChild(elem);
    }
}

//ookie) {
//ies) {
//
//
//
//
//

function newTask() {
    var inputTask = prompt("Add new task");
    var div = document.createElement("div");
    var task = document.createTextNode(inputTask);
    div.appendChild(task);
    if (inputTask === '' || !inputTask) {
        alert("You must write something!");
    } else {
        div.className = "task";
        document.getElementById("ft_list").prepend(div);
        div.setAttribute("onClick", "remover(this);");
    }
    document.getElementById("newTask").value = "";

    for (i = 0; i < remove.length; i++) {
        remove[i].onclick = function () {
            var div = this;
            div.style.display = "none";
        }
    }
}
