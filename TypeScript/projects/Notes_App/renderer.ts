import * as fs from 'fs';
import * as path from 'path';

const notesFile = path.join(__dirname, 'notes.json');

type Priority = 'High' | 'Medium' | 'Low';

interface Note {
    id: number;
    text: string;
    tags: string[];
    timestamp: string;
    priority: Priority;
}

// History for undo/redo
let history: Note[][] = [];
let historyIndex = -1;

function loadNotes(): Note[] {
    if (fs.existsSync(notesFile)) {
        return JSON.parse(fs.readFileSync(notesFile, 'utf-8'));
    }
    return [];
}

function saveNotes(notes: Note[]) {
    fs.writeFileSync(notesFile, JSON.stringify(notes, null, 2));
    pushHistory(notes);
}

function pushHistory(notes: Note[]) {
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

function generateId(): number {
    return Date.now();
}

function addNote(text: string, tags: string[], priority: Priority) {
    const notes = loadNotes();
    notes.push({ id: generateId(), text, tags, timestamp: new Date().toLocaleString(), priority });
    saveNotes(notes);
    renderNotes();
}

function editNote(id: number, newText: string, newTags: string[], newPriority: Priority) {
    const notes = loadNotes();
    const note = notes.find(n => n.id === id);
    if (note) {
        note.text = newText;
        note.tags = newTags;
        note.priority = newPriority;
        note.timestamp = new Date().toLocaleString();
        saveNotes(notes);
        renderNotes();
    }
}

function deleteNote(id: number) {
    let notes = loadNotes();
    notes = notes.filter(n => n.id !== id);
    saveNotes(notes);
    renderNotes();
}

function renderNotes(filteredNotes?: Note[], filterText: string = '') {
    const list = document.getElementById('notesList')!;
    list.innerHTML = '';
    let notes = filteredNotes || loadNotes();

    // Filter by text/tags
    notes = notes.filter(n => n.text.toLowerCase().includes(filterText.toLowerCase()) || n.tags.join(' ').toLowerCase().includes(filterText.toLowerCase()));

    notes.forEach(note => {
        const li = document.createElement('li');
        li.className = 'note';

        // Color coding by priority
        let color = '#fff';
        if (note.priority === 'High') color = '#f8d7da';
        else if (note.priority === 'Medium') color = '#fff3cd';
        else color = '#d4edda';
        li.style.backgroundColor = color;

        const span = document.createElement('span');
        span.textContent = `[${note.priority}] ${note.text} [Tags: ${note.tags.join(', ')}] (Added: ${note.timestamp})`;

        const editBtn = document.createElement('button');
        editBtn.textContent = 'Edit';
        editBtn.onclick = () => {
            const newText = prompt('Edit note text:', note.text);
            const newTags = prompt('Edit tags (comma separated):', note.tags.join(','))?.split(',').map(t => t.trim()) || [];
            const newPriority = (prompt('Edit priority (High, Medium, Low):', note.priority) as Priority) || note.priority;
            if (newText) editNote(note.id, newText, newTags, newPriority);
        };

        const delBtn = document.createElement('button');
        delBtn.textContent = 'Delete';
        delBtn.onclick = () => deleteNote(note.id);

        li.appendChild(span);
        li.appendChild(editBtn);
        li.appendChild(delBtn);
        list.appendChild(li);
    });
}

// DOM elements
const searchInput = document.getElementById('search') as HTMLInputElement;
const addBtn = document.getElementById('addBtn')!;
const noteInput = document.getElementById('noteInput') as HTMLInputElement;
const tagsInput = document.getElementById('tagsInput') as HTMLInputElement;
const priorityInput = document.createElement('select');

['High', 'Medium', 'Low'].forEach(p => {
    const option = document.createElement('option');
    option.value = p;
    option.text = p;
    priorityInput.appendChild(option);
});
document.getElementById('controls')!.appendChild(priorityInput);

// Add note
addBtn.addEventListener('click', () => {
    if (noteInput.value.trim() !== '') {
        const tags = tagsInput.value.split(',').map(t => t.trim()).filter(t => t);
        const priority = priorityInput.value as Priority;
        addNote(noteInput.value.trim(), tags, priority);
        noteInput.value = '';
        tagsInput.value = '';
    }
});

// Search
searchInput.addEventListener('input', () => renderNotes(undefined, searchInput.value));

// Export
const exportBtn = document.getElementById('exportBtn')!;
exportBtn.addEventListener('click', () => {
    const notes = loadNotes();
    const exportPath = path.join(__dirname, `notes_export_${Date.now()}.json`);
    fs.writeFileSync(exportPath, JSON.stringify(notes, null, 2));
    alert(`Notes exported to ${exportPath}`);
});

// Undo / Redo buttons
const undoBtn = document.createElement('button');
undoBtn.textContent = 'Undo';
undoBtn.onclick = undo;
const redoBtn = document.createElement('button');
redoBtn.textContent = 'Redo';
redoBtn.onclick = redo;

document.getElementById('controls')!.appendChild(undoBtn);
document.getElementById('controls')!.appendChild(redoBtn);

// Initial render
renderNotes();