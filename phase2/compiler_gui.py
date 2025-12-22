#!/usr/bin/env python3
"""
SimpleLang Compiler - Phase 2
GUI Application

A simple graphical interface for the SimpleLang compiler.
Features:
- Code editor with syntax highlighting
- Compile button
- Output display (quadruples, errors)
- Symbol table display
"""

import tkinter as tk
from tkinter import filedialog, scrolledtext, messagebox, ttk
import subprocess
import os
import sys
import re

class SimpleLangGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("SimpleLang Compiler - Phase 2")
        self.root.geometry("1200x800")
        
        # Configure colors
        self.bg_color = "#2b2b2b"
        self.fg_color = "#a9b7c6"
        self.keyword_color = "#cc7832"
        self.string_color = "#6a8759"
        self.number_color = "#6897bb"
        self.comment_color = "#808080"
        
        # Create main container
        self.main_frame = ttk.Frame(root, padding="5")
        self.main_frame.pack(fill="both", expand=True)
        
        # Create menu bar
        self.create_menu()
        
        # Create toolbar
        self.create_toolbar()
        
        # Create paned window for resizable sections
        self.paned = ttk.PanedWindow(self.main_frame, orient=tk.VERTICAL)
        self.paned.pack(fill="both", expand=True, pady=5)
        
        # Code editor frame
        self.editor_frame = ttk.LabelFrame(self.paned, text="Source Code", padding="5")
        self.paned.add(self.editor_frame, weight=2)
        
        # Code editor
        self.code_editor = scrolledtext.ScrolledText(
            self.editor_frame,
            width=120,
            height=20,
            font=("Consolas", 11),
            bg="#1e1e1e",
            fg="#d4d4d4",
            insertbackground="white",
            wrap=tk.NONE
        )
        self.code_editor.pack(fill="both", expand=True)
        
        # Add horizontal scrollbar
        h_scroll = ttk.Scrollbar(self.editor_frame, orient=tk.HORIZONTAL, 
                                  command=self.code_editor.xview)
        h_scroll.pack(fill="x")
        self.code_editor.config(xscrollcommand=h_scroll.set)
        
        # Bind key events for syntax highlighting
        self.code_editor.bind('<KeyRelease>', self.highlight_syntax)
        
        # Output notebook (tabs for different outputs)
        self.output_notebook = ttk.Notebook(self.paned)
        self.paned.add(self.output_notebook, weight=1)
        
        # Quadruples tab
        self.quads_frame = ttk.Frame(self.output_notebook)
        self.output_notebook.add(self.quads_frame, text="Quadruples")
        
        self.quads_text = scrolledtext.ScrolledText(
            self.quads_frame,
            width=120,
            height=10,
            font=("Consolas", 10),
            bg="#1a1a1a",
            fg="#00ff00",
            state="disabled"
        )
        self.quads_text.pack(fill="both", expand=True)
        
        # Errors/Warnings tab
        self.errors_frame = ttk.Frame(self.output_notebook)
        self.output_notebook.add(self.errors_frame, text="Errors & Warnings")
        
        self.errors_text = scrolledtext.ScrolledText(
            self.errors_frame,
            width=120,
            height=10,
            font=("Consolas", 10),
            bg="#1a1a1a",
            fg="#ff6b6b",
            state="disabled"
        )
        self.errors_text.pack(fill="both", expand=True)
        
        # Symbol Table tab
        self.symtab_frame = ttk.Frame(self.output_notebook)
        self.output_notebook.add(self.symtab_frame, text="Symbol Table")
        
        self.symtab_text = scrolledtext.ScrolledText(
            self.symtab_frame,
            width=120,
            height=10,
            font=("Consolas", 10),
            bg="#1a1a1a",
            fg="#87ceeb",
            state="disabled"
        )
        self.symtab_text.pack(fill="both", expand=True)
        
        # Console tab
        self.console_frame = ttk.Frame(self.output_notebook)
        self.output_notebook.add(self.console_frame, text="Console")
        
        self.console_text = scrolledtext.ScrolledText(
            self.console_frame,
            width=120,
            height=10,
            font=("Consolas", 10),
            bg="#1a1a1a",
            fg="#ffffff",
            state="disabled"
        )
        self.console_text.pack(fill="both", expand=True)
        
        # Status bar
        self.status_var = tk.StringVar()
        self.status_var.set("Ready")
        self.status_bar = ttk.Label(self.main_frame, textvariable=self.status_var, 
                                     relief="sunken", anchor="w")
        self.status_bar.pack(fill="x", pady=(5, 0))
        
        # Current file path
        self.current_file = None
        
        # Insert sample code
        self.insert_sample_code()
        
    def create_menu(self):
        menubar = tk.Menu(self.root)
        self.root.config(menu=menubar)
        
        # File menu
        file_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="New", command=self.new_file, accelerator="Ctrl+N")
        file_menu.add_command(label="Open...", command=self.open_file, accelerator="Ctrl+O")
        file_menu.add_command(label="Save", command=self.save_file, accelerator="Ctrl+S")
        file_menu.add_command(label="Save As...", command=self.save_file_as)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.root.quit)
        
        # Edit menu
        edit_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Edit", menu=edit_menu)
        edit_menu.add_command(label="Cut", command=lambda: self.code_editor.event_generate("<<Cut>>"))
        edit_menu.add_command(label="Copy", command=lambda: self.code_editor.event_generate("<<Copy>>"))
        edit_menu.add_command(label="Paste", command=lambda: self.code_editor.event_generate("<<Paste>>"))
        edit_menu.add_separator()
        edit_menu.add_command(label="Clear All", command=self.clear_all)
        
        # Build menu
        build_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Build", menu=build_menu)
        build_menu.add_command(label="Compile", command=self.compile_code, accelerator="F5")
        build_menu.add_command(label="Clear Output", command=self.clear_output)
        
        # Help menu
        help_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Help", menu=help_menu)
        help_menu.add_command(label="Language Reference", command=self.show_help)
        help_menu.add_command(label="About", command=self.show_about)
        
        # Bind keyboard shortcuts
        self.root.bind('<Control-n>', lambda e: self.new_file())
        self.root.bind('<Control-o>', lambda e: self.open_file())
        self.root.bind('<Control-s>', lambda e: self.save_file())
        self.root.bind('<F5>', lambda e: self.compile_code())
        
    def create_toolbar(self):
        toolbar = ttk.Frame(self.main_frame)
        toolbar.pack(fill="x", pady=(0, 5))
        
        # Buttons with icons (using text for simplicity)
        ttk.Button(toolbar, text="📄 New", command=self.new_file).pack(side="left", padx=2)
        ttk.Button(toolbar, text="📂 Open", command=self.open_file).pack(side="left", padx=2)
        ttk.Button(toolbar, text="💾 Save", command=self.save_file).pack(side="left", padx=2)
        
        ttk.Separator(toolbar, orient="vertical").pack(side="left", fill="y", padx=5)
        
        ttk.Button(toolbar, text="▶️ Compile", command=self.compile_code).pack(side="left", padx=2)
        ttk.Button(toolbar, text="🧹 Clear", command=self.clear_output).pack(side="left", padx=2)
        
        ttk.Separator(toolbar, orient="vertical").pack(side="left", fill="y", padx=5)
        
        ttk.Button(toolbar, text="📖 Help", command=self.show_help).pack(side="left", padx=2)
        
    def insert_sample_code(self):
        sample = '''// SimpleLang Sample Program
// Phase 2 - With semantic analysis and quadruples

// Variable declarations
rakam x = 10;
rakam y = 20;
kasr pi = 3.14159;
kalam msg = "Marhaba!";
mantiq flag = sa7;

// Constant declaration
sabit rakam MAX = 100;

// Arithmetic expression
rakam result = x + y * 2;

// Print statement
etba3 msg;
etba3 result;

// Conditional statement
law (x < y) {
    etba3 "x is less than y";
    x = x + 1;
} wella {
    etba3 "x is greater or equal to y";
}

// While loop
tool ma (x < 15) {
    etba3 x;
    x = x + 1;
}

// For loop
lef (rakam i = 0; i < 5; i++) {
    etba3 i;
}

// Function definition
shoghla rakam add(rakam a, rakam b) {
    ragga3 a + b;
}

// Switch statement
ekhtar (x) {
    7ala 10:
        etba3 "x is 10";
        ekhla3;
    7ala 15:
        etba3 "x is 15";
        ekhla3;
    asasya:
        etba3 "x is something else";
}
'''
        self.code_editor.insert("1.0", sample)
        self.highlight_syntax()
        
    def highlight_syntax(self, event=None):
        # Remove existing tags
        for tag in ["keyword", "type", "string", "number", "comment", "bool"]:
            self.code_editor.tag_remove(tag, "1.0", "end")
        
        content = self.code_editor.get("1.0", "end")
        
        # Define patterns
        keywords = r'\b(law|wella|tool ma|lef|karrar|le7ad|shoghla|ragga3|etba3|ekhtar|7ala|asasya|ekhla3|kamel|sabit)\b'
        types = r'\b(rakam|kasr|kalam|mantiq)\b'
        booleans = r'\b(sa7|ghalat)\b'
        strings = r'"[^"]*"'
        numbers = r'\b\d+\.?\d*\b'
        comments = r'//.*$'
        
        # Apply highlighting
        self.apply_tag("keyword", keywords, "#cc7832")
        self.apply_tag("type", types, "#4ec9b0")
        self.apply_tag("bool", booleans, "#569cd6")
        self.apply_tag("string", strings, "#ce9178")
        self.apply_tag("number", numbers, "#b5cea8")
        self.apply_tag("comment", comments, "#6a9955")
        
    def apply_tag(self, tag_name, pattern, color):
        self.code_editor.tag_config(tag_name, foreground=color)
        content = self.code_editor.get("1.0", "end")
        
        for match in re.finditer(pattern, content, re.MULTILINE):
            start = f"1.0+{match.start()}c"
            end = f"1.0+{match.end()}c"
            self.code_editor.tag_add(tag_name, start, end)
            
    def new_file(self):
        if self.code_editor.get("1.0", "end-1c"):
            if messagebox.askyesno("New File", "Clear current code?"):
                self.code_editor.delete("1.0", "end")
                self.current_file = None
                self.status_var.set("New file")
                
    def open_file(self):
        path = filedialog.askopenfilename(
            filetypes=[
                ("SimpleLang Files", "*.sl"),
                ("All Files", "*.*")
            ]
        )
        if path:
            try:
                with open(path, "r", encoding="utf-8") as f:
                    content = f.read()
                self.code_editor.delete("1.0", "end")
                self.code_editor.insert("1.0", content)
                self.current_file = path
                self.status_var.set(f"Opened: {path}")
                self.highlight_syntax()
            except Exception as e:
                messagebox.showerror("Error", f"Could not open file:\n{e}")
                
    def save_file(self):
        if self.current_file:
            try:
                with open(self.current_file, "w", encoding="utf-8") as f:
                    f.write(self.code_editor.get("1.0", "end-1c"))
                self.status_var.set(f"Saved: {self.current_file}")
            except Exception as e:
                messagebox.showerror("Error", f"Could not save file:\n{e}")
        else:
            self.save_file_as()
            
    def save_file_as(self):
        path = filedialog.asksaveasfilename(
            defaultextension=".sl",
            filetypes=[
                ("SimpleLang Files", "*.sl"),
                ("All Files", "*.*")
            ]
        )
        if path:
            self.current_file = path
            self.save_file()
            
    def clear_all(self):
        if messagebox.askyesno("Clear All", "Clear all code?"):
            self.code_editor.delete("1.0", "end")
            
    def clear_output(self):
        for text_widget in [self.quads_text, self.errors_text, 
                           self.symtab_text, self.console_text]:
            text_widget.config(state="normal")
            text_widget.delete("1.0", "end")
            text_widget.config(state="disabled")
        self.status_var.set("Output cleared")
        
    def compile_code(self):
        self.status_var.set("Compiling...")
        self.root.update()
        
        # Clear previous output
        self.clear_output()
        
        # Get code
        code = self.code_editor.get("1.0", "end")
        
        # Write to temp file
        script_dir = os.path.dirname(os.path.abspath(__file__))
        temp_file = os.path.join(script_dir, "temp_input.sl")
        
        try:
            with open(temp_file, "w", encoding="utf-8") as f:
                f.write(code)
        except Exception as e:
            self.show_error(f"Could not write temp file: {e}")
            return
        
        # Find compiler executable
        if sys.platform == "win32":
            compiler_paths = [
                os.path.join(script_dir, "compiler.exe"),
                os.path.join(script_dir, "compiler"),
                "./compiler.exe",
                "./compiler"
            ]
        else:
            compiler_paths = [
                os.path.join(script_dir, "compiler"),
                "./compiler"
            ]
        
        compiler = None
        for path in compiler_paths:
            if os.path.exists(path):
                compiler = path
                break
        
        if not compiler:
            self.show_error("Compiler executable not found.\n\nPlease build the compiler first:\n  make\nor\n  make windows")
            self.status_var.set("Compiler not found")
            return
        
        # Run compiler
        try:
            result = subprocess.run(
                [compiler, temp_file],
                capture_output=True,
                text=True,
                timeout=30,
                cwd=script_dir
            )
            
            stdout = result.stdout
            stderr = result.stderr
            
            # Parse and display output
            self.display_output(stdout, stderr)
            
            # Read symbol table file
            symtab_file = os.path.join(script_dir, "symbols.txt")
            if os.path.exists(symtab_file):
                try:
                    with open(symtab_file, "r", encoding="utf-8") as f:
                        symtab = f.read()
                    self.symtab_text.config(state="normal")
                    self.symtab_text.insert("end", symtab)
                    self.symtab_text.config(state="disabled")
                except:
                    pass
            
            if result.returncode == 0:
                self.status_var.set("Compilation successful!")
            else:
                self.status_var.set("Compilation finished with errors")
                
        except subprocess.TimeoutExpired:
            self.show_error("Compilation timed out")
            self.status_var.set("Timeout")
        except Exception as e:
            self.show_error(f"Compilation error:\n{e}")
            self.status_var.set("Error")
        finally:
            # Clean up temp file
            try:
                os.remove(temp_file)
            except:
                pass
                
    def display_output(self, stdout, stderr):
        # Display full console output
        self.console_text.config(state="normal")
        self.console_text.insert("end", stdout)
        if stderr:
            self.console_text.insert("end", "\n--- STDERR ---\n")
            self.console_text.insert("end", stderr)
        self.console_text.config(state="disabled")
        
        # Extract quadruples section
        quads_match = re.search(r'=== Generated Quadruples ===.*?(?=\n===|\Z)', 
                                stdout, re.DOTALL)
        if quads_match:
            self.quads_text.config(state="normal")
            self.quads_text.insert("end", quads_match.group(0))
            self.quads_text.config(state="disabled")
        
        # Display errors and warnings
        self.errors_text.config(state="normal")
        
        # Extract errors from stderr
        if stderr:
            self.errors_text.insert("end", "=== ERRORS ===\n", "error")
            self.errors_text.insert("end", stderr)
        
        # Extract warnings from stdout
        warning_pattern = r'Warning.*'
        warnings = re.findall(warning_pattern, stdout)
        if warnings:
            self.errors_text.insert("end", "\n=== WARNINGS ===\n")
            for w in warnings:
                self.errors_text.insert("end", w + "\n")
        
        self.errors_text.config(state="disabled")
        
        # Switch to appropriate tab
        if stderr:
            self.output_notebook.select(self.errors_frame)
        else:
            self.output_notebook.select(self.quads_frame)
            
    def show_error(self, message):
        self.errors_text.config(state="normal")
        self.errors_text.insert("end", message)
        self.errors_text.config(state="disabled")
        self.output_notebook.select(self.errors_frame)
        
    def show_help(self):
        help_text = """
SimpleLang Language Reference
=============================

Keywords (Arabic Transliteration):
---------------------------------
rakam      - Integer type
kasr       - Float type
kalam      - String type
mantiq     - Boolean type
sabit      - Constant declaration

law        - If statement
wella      - Else clause
tool ma    - While loop
lef        - For loop
karrar     - Do-while
le7ad      - Until

shoghla    - Function declaration
ragga3     - Return statement
etba3      - Print statement

ekhtar     - Switch statement
7ala       - Case clause
asasya     - Default clause
ekhla3     - Break statement
kamel      - Continue statement

Boolean values:
sa7        - True
ghalat     - False

Operators:
---------
+, -, *, /, %    - Arithmetic
<, >, <=, >=     - Comparison
==, !=           - Equality
&&, ||, !        - Logical
=                - Assignment
+=, -=, *=, /=   - Compound assignment
++, --           - Increment/Decrement

Example:
-------
rakam x = 10;
law (x > 5) {
    etba3 "x is greater than 5";
}
"""
        help_window = tk.Toplevel(self.root)
        help_window.title("Language Reference")
        help_window.geometry("600x500")
        
        text = scrolledtext.ScrolledText(help_window, font=("Consolas", 11))
        text.pack(fill="both", expand=True, padx=10, pady=10)
        text.insert("1.0", help_text)
        text.config(state="disabled")
        
    def show_about(self):
        messagebox.showinfo(
            "About SimpleLang Compiler",
            "SimpleLang Compiler - Phase 2\n\n"
            "Features:\n"
            "• Symbol table with scoping\n"
            "• Quadruple generation\n"
            "• Semantic analysis\n"
            "• Error recovery\n\n"
            "A custom programming language with Arabic-style keywords."
        )


def main():
    root = tk.Tk()
    app = SimpleLangGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
