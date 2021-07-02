var statusElement = document.getElementById("status");
var progressElement = document.getElementById("progress");
var spinnerElement = document.getElementById("spinner");

function setScore(score) {
    let p = document.getElementById("score");
    p.innerHTML = `Score: ${score}`;
}

function setMoves(moves) {
    let p = document.getElementById("moves");
    p.innerHTML = `Moves: ${moves}`;
}

function showGameOver() {
    let p = document.getElementById("gameover");
    p.style.display = "block";
}

function toggleConsole() {
    let console = document.getElementById("output");
    if (console.style.display == "block") console.style.display = "none";
    else console.style.display = "block";
}

// -- SET CANVAS SIZE --
const canvas = document.getElementById("canvas");
const vw = Math.max(
    document.documentElement.clientWidth || 0,
    window.innerWidth || 0
);
const vh = Math.max(
    document.documentElement.clientHeight || 0,
    window.innerHeight || 0
);
console.log({ vw, vh });
canvas.width = 300;
canvas.height = 200;
// ----

var Module = {
    preRun: [],
    postRun: [],
    print: (function () {
        var element = document.getElementById("output");
        if (element) element.value = ""; // clear browser cache
        return function (text) {
            if (arguments.length > 1)
                text = Array.prototype.slice.call(arguments).join(" ");
            // These replacements are necessary if you render to raw HTML
            //text = text.replace(/&/g, "&amp;");
            //text = text.replace(/</g, "&lt;");
            //text = text.replace(/>/g, "&gt;");
            //text = text.replace('\n', '<br>', 'g');
            console.log(text);
            if (element) {
                element.value += text + "\n";
                element.scrollTop = element.scrollHeight; // focus on bottom
            }
        };
    })(),
    printErr: function (text) {
        if (arguments.length > 1)
            text = Array.prototype.slice.call(arguments).join(" ");
        console.error(text);
    },
    canvas: (function () {
        var canvas = document.getElementById("canvas");

        // As a default initial behavior, pop up an alert when webgl context is lost. To make your
        // application robust, you may want to override this behavior before shipping!
        // See http://www.khronos.org/registry/webgl/specs/latest/1.0/#5.15.2
        canvas.addEventListener(
            "webglcontextlost",
            function (e) {
                alert("WebGL context lost. You will need to reload the page.");
                e.preventDefault();
            },
            false
        );

        return canvas;
    })(),
    setStatus: function (text) {
        if (!Module.setStatus.last)
            Module.setStatus.last = { time: Date.now(), text: "" };
        if (text === Module.setStatus.last.text) return;
        var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
        var now = Date.now();
        if (m && now - Module.setStatus.last.time < 30) return; // if this is a progress update, skip it if too soon
        Module.setStatus.last.time = now;
        Module.setStatus.last.text = text;
        if (m) {
            text = m[1];
            progressElement.value = parseInt(m[2]) * 100;
            progressElement.max = parseInt(m[4]) * 100;
            progressElement.hidden = false;
            spinnerElement.hidden = false;
        } else {
            progressElement.value = null;
            progressElement.max = null;
            progressElement.hidden = true;
            if (!text) spinnerElement.style.display = "none";
        }
        statusElement.innerHTML = text;
    },
    totalDependencies: 0,
    monitorRunDependencies: function (left) {
        this.totalDependencies = Math.max(this.totalDependencies, left);
        Module.setStatus(
            left
                ? "Preparing... (" +
                      (this.totalDependencies - left) +
                      "/" +
                      this.totalDependencies +
                      ")"
                : "All downloads complete."
        );
    },
};
Module.setStatus("Downloading...");
window.onerror = function (event) {
    // TODO: do not warn on ok events like simulating an infinite loop or exitStatus
    Module.setStatus("Exception thrown, see JavaScript console");
    spinnerElement.style.display = "none";
    Module.setStatus = function (text) {
        if (text) Module.printErr("[post-exception status] " + text);
    };
};
