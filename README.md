# Browser History Simulator (C Project)

## Overview
The **Browser History Simulator** is a console-based project implemented in **C** using a **Doubly Linked List**.  
It simulates how a real browser manages user navigation — visiting new websites, going back, and going forward — along with saving and loading history from a file.

This project demonstrates key **data structure concepts** like **linked lists**, **dynamic memory allocation**, and **file handling** in C.

---

## Features

| Feature | Description |
|----------|--------------|
| 🆕 Visit Website | Visit a new website and add it to your history |
| 🔙 Go Back | Move back to the previously visited website |
| 🔜 Go Forward | Move forward to the next website |
| 📜 Show History | Display the entire browsing history (marking the current page) |
| 💾 Save History | Automatically save browsing history to `history.txt` |
| 📂 Load History | Load previous history on startup |
| ❌ Exit | Exit safely and free allocated memory |
---

## ⚙️ Data Structure Used
### Doubly Linked List
Each node represents a web page (URL)
---

## Working Logic

###  Visiting a New Website
1. Create a new node for the entered **URL**.  
2. Delete all **forward pages** (as happens in a real browser when you visit a new site after going back).  
3. Link the **new node** after the current node.  
4. Move the **current pointer** to this new node.

---

###  Going Back / Forward

- **Go Back:**  
  Move the `current` pointer to `current->prev` (the previous node in the doubly linked list).  

- **Go Forward:**  
  Move the `current` pointer to `current->next` (the next node in the doubly linked list).  

---

### Saving & Loading

- All visited URLs are stored **line-by-line** in a text file named **`history.txt`**.  
- When the program **starts**, it reads this file and **rebuilds the linked list**, restoring the browsing history.  
- On **exit**, it writes the **entire current history** back to the file, preserving the session for the next run.

---
