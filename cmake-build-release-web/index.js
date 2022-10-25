var file = null;
var filedata = null;

function compress() {
    const dict_size = document.getElementById('dictSizeInput').value;
    const buffer_size = document.getElementById('bufferSizeInput').value;
    const filename = file.name;
    console.log(filename);
    const new_filename = filename + ".hf.lz";
    console.log(new_filename);

    const timer_begin = new Date();
    const result = Module.HSCompress(filedata, dict_size | 0, buffer_size | 0)
    const timer_end = new Date();

    const elapsed = timer_end - timer_begin;
    document.getElementById('elapsed_time').innerText = elapsed.toString();
    setTimeout(() => document.getElementById('elapsed_time').innerText = '', 3000);
    console.log("elapsed: " + elapsed);

    return [result, new_filename];
}

function decompress() {
    const filename = file.name;
    console.log(filename);
    if (!filename.endsWith('.hf.lz'))
        throw 'file name must end with ".hf.lz"';
    const new_filename = filename.substring(0, filename.lastIndexOf('.hf.lz'));
    console.log(new_filename);

    const timer_begin = new Date();
    const result = Module.HSDecompress(filedata);
    const timer_end = new Date();

    const elapsed = timer_end - timer_begin;
    console.log("elapsed: " + elapsed);

    return [result, new_filename];
}


function onRunClick() {
    const isCompress = document.getElementById('compress_switch').checked;
    const [result, filename] = isCompress ? compress() : decompress();

    const blob = new Blob([result], {type: "text/plain"});

    const a = document.getElementById('saveButton');
    a.href = URL.createObjectURL(blob);
    a.download = filename;
    document.getElementById('saveButton').classList.remove('disabled');
}

function onFile(evt) {
    const inputfiles = evt.target.files;
    if (inputfiles.length !== 1)
        throw "Many files not supported";
    const inputfile = inputfiles[0];
    file = inputfile;   // global

    document.getElementById('runButton').classList.add('disabled');
    document.getElementById('saveButton').classList.add('disabled');

    const reader = new FileReader();
    reader.onload = event => {
        filedata = event.target.result; // global
        document.getElementById('runButton').classList.remove('disabled');
    };
    reader.readAsArrayBuffer(inputfile);
}

var Module = {
    onRuntimeInitialized: function () {
        console.log("upper result: " + Module.toupper("aboba"));
    },
};


document.getElementById('fileInput').addEventListener('change', onFile);
