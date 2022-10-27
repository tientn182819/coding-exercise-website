const left = document.querySelector(".hlw-leftside"),
    right = document.querySelector(".hlw-rightside"),
    bar = document.querySelector(".hlw-bar"),
    editor = document.querySelector(".hlw-editor"),
    run = document.querySelector(".btn-run"),
    iframe = document.querySelector(".hlw-iframe");



const drag = (e) => {
    e.preventDefault();
    document.selection ? document.selection.empty() : window.getSelection().removeAllRanges();
    left.style.width = (e.pageX - bar.offsetWidth / 3) + "px";
    editor.resize();
}

bar.addEventListener("mousedown", () => {
    document.addEventListener("mousemove", drag);
})

bar.addEventListener("mouseup", () => {
    document.removeEventListener("mousemove", drag);
})

// //Run btn event listener
// run.addEventListener("click", () => {
//     const html = editor.textContent;
//     iframe.src = "data:text/html;charset=utf-8," + encodeURI(html);
// })