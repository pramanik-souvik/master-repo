"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs");
var path = require("path");
var notesFile = path.join(__dirname, 'notes.json');
// History for undo/redo
var history = [];
var historyIndex = -1;
function loadNotes() {
    if (fs.existsSync(notesFile)) {
        return JSON.parse(fs.readFileSync(notesFile, 'utf-8'));
    }
    return [];
}
function saveNotes(notes) {
    fs.writeFileSync(notesFile, JSON.stringify(notes, null, 2));
    pushHistory(notes);
}
function pushHistory(notes) {
    history = history.slice(0, historyIndex + 1);
    history.push(JSON.parse(JSON.stringify(notes))); // deep copy
    historyIndex++;
}
function undo() {
    if (historyIndex > 0) {
        historyIndex--;
        renderNotes(history[historyIndex]);
    }
}
function redo() {
    if (historyIndex < history.length - 1) {
        historyIndex++;
        renderNotes(history[historyIndex]);
    }
}
function generateId() {
    return Date.now();
}
function addNote(text, tags, priority) {
    var notes = loadNotes();
    notes.push({ id: generateId(), text: text, tags: tags, timestamp: new Date().toLocaleString(), priority: priority });
    saveNotes(notes);
    renderNotes();
}
function editNote(id, newText, newTags, newPriority) {
    var notes = loadNotes();
    var note = notes.find(function (n) { return n.id === id; });
    if (note) {
        note.text = newText;
        note.tags = newTags;
        note.priority = newPriority;
        note.timestamp = new Date().toLocaleString();
        saveNotes(notes);
        renderNotes();
    }
}
function deleteNote(id) {
    var notes = loadNotes();
    notes = notes.filter(function (n) { return n.id !== id; });
    saveNotes(notes);
    renderNotes();
}
function renderNotes(filteredNotes, filterText) {
    if (filterText === void 0) { filterText = ''; }
    var list = document.getElementById('notesList');
    list.innerHTML = '';
    var notes = filteredNotes || loadNotes();
    // Filter by text/tags
    notes = notes.filter(function (n) { return n.text.toLowerCase().includes(filterText.toLowerCase()) || n.tags.join(' ').toLowerCase().includes(filterText.toLowerCase()); });
    notes.forEach(function (note) {
        var li = document.createElement('li');
        li.className = 'note';
        // Color coding by priority
        var color = '#fff';
        if (note.priority === 'High')
            color = '#f8d7da';
        else if (note.priority === 'Medium')
            color = '#fff3cd';
        else
            color = '#d4edda';
        li.style.backgroundColor = color;
        var span = document.createElement('span');
        span.textContent = "[".concat(note.priority, "] ").concat(note.text, " [Tags: ").concat(note.tags.join(', '), "] (Added: ").concat(note.timestamp, ")");
        var editBtn = document.createElement('button');
        editBtn.textContent = 'Edit';
        editBtn.onclick = function () {
            var _a;
            var newText = prompt('Edit note text:', note.text);
            var newTags = ((_a = prompt('Edit tags (comma separated):', note.tags.join(','))) === null || _a === void 0 ? void 0 : _a.split(',').map(function (t) { return t.trim(); })) || [];
            var newPriority = prompt('Edit priority (High, Medium, Low):', note.priority) || note.priority;
            if (newText)
                editNote(note.id, newText, newTags, newPriority);
        };
        var delBtn = document.createElement('button');
        delBtn.textContent = 'Delete';
        delBtn.onclick = function () { return deleteNote(note.id); };
        li.appendChild(span);
        li.appendChild(editBtn);
        li.appendChild(delBtn);
        list.appendChild(li);
    });
}
// DOM elements
var searchInput = document.getElementById('search');
var addBtn = document.getElementById('addBtn');
var noteInput = document.getElementById('noteInput');
var tagsInput = document.getElementById('tagsInput');
var priorityInput = document.createElement('select');
['High', 'Medium', 'Low'].forEach(function (p) {
    var option = document.createElement('option');
    option.value = p;
    option.text = p;
    priorityInput.appendChild(option);
});
document.getElementById('controls').appendChild(priorityInput);
// Add note
addBtn.addEventListener('click', function () {
    if (noteInput.value.trim() !== '') {
        var tags = tagsInput.value.split(',').map(function (t) { return t.trim(); }).filter(function (t) { return t; });
        var priority = priorityInput.value;
        addNote(noteInput.value.trim(), tags, priority);
        noteInput.value = '';
        tagsInput.value = '';
    }
});
// Search
searchInput.addEventListener('input', function () { return renderNotes(undefined, searchInput.value); });
// Export
var exportBtn = document.getElementById('exportBtn');
exportBtn.addEventListener('click', function () {
    var notes = loadNotes();
    var exportPath = path.join(__dirname, "notes_export_".concat(Date.now(), ".json"));
    fs.writeFileSync(exportPath, JSON.stringify(notes, null, 2));
    alert("Notes exported to ".concat(exportPath));
});
// Undo / Redo buttons
var undoBtn = document.createElement('button');
undoBtn.textContent = 'Undo';
undoBtn.onclick = undo;
var redoBtn = document.createElement('button');
redoBtn.textContent = 'Redo';
redoBtn.onclick = redo;
document.getElementById('controls').appendChild(undoBtn);
document.getElementById('controls').appendChild(redoBtn);
// Initial render
renderNotes();
