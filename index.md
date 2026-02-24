---
title: Assignments
layout: default
---

<!--
Landing page with 20/80 split.
- Left: index (sticky)
- Right: content rendered from root-level .md files (not raw)
- Hides logo, "View the Project on GitHub", and footer text on THIS page only.
- Keeps ALL files at repo root.
-->

<style>
/* Hide GitHub Pages theme chrome ONLY on this page */
.page-header,            /* top banner with title/tagline in jekyll-theme-minimal */
.site-footer,            /* bottom footer area */
a.btn[href*="github.com"]/* "View the Project on GitHub" button */ {
  display: none !important;
}

/* Page layout variables */
:root {
  --left: 20%;
  --right: 80%;
  --border: #e5e7eb;
  --bg: #ffffff;
  --text: #0f172a;
  --text-hover: #111827;
}

body {
  margin: 0;
  padding: 0;
}

.main-container {
  display: grid;
  grid-template-columns: var(--left) var(--right);
  gap: 12px;
  padding: 12px;
}

/* LEFT SIDEBAR */
.sidebar {
  position: sticky;
  top: 0;
  height: calc(100vh - 24px);
  border: 1px solid var(--border);
  border-radius: 8px;
  padding: 12px;
  background: var(--bg);
  overflow-y: auto;
}

.sidebar h3 {
  margin: 4px 0 10px;
  font-size: 1.05rem;
}

.sidebar a {
  display: block;
  padding: 6px 8px;
  margin-bottom: 6px;
  color: var(--text);
  text-decoration: none;
  border-radius: 6px;
  border: 1px solid transparent;
}

.sidebar a:hover,
.sidebar a.active {
  background: #eef2ff;
  border-color: #c7d2fe;
  color: var(--text-hover);
}

/* RIGHT CONTENT AREA */
.content-box {
  border: 1px solid var(--border);
  border-radius: 8px;
  padding: 16px;
  background: var(--bg);
  height: calc(100vh - 24px);
  overflow-y: auto;
}

/* RESPONSIVE */
@media (max-width: 900px) {
  .main-container {
    grid-template-columns: 1fr;
  }
  .sidebar {
    position: relative;
    height: auto;
  }
  .content-box {
    height: auto;
    min-height: 60vh;
  }
}
</style>

<div class="main-container">

  <!-- LEFT SIDEBAR -->
  <div class="sidebar" id="apexNav">
    <h3>Assignments</h3>
    <a href="#signal.md"     data-file="signal.md">Signals</a>
    <a href="#thread.md"     data-file="thread.md">Threads</a>
    <hr>
    <strong>POSIX IPC</strong>
    <a href="#posixpipe.md"  data-file="posixpipe.md">Pipes (Unnamed)</a>
    <a href="#posixfifo.md"  data-file="posixfifo.md">FIFOs (Named Pipes)</a>
    <a href="#posixshm.md"   data-file="posixshm.md">Shared Memory</a>
    <a href="#posixmsgque.md"data-file="posixmsgque.md">Message Queues</a>
  </div>

  <!-- RIGHT CONTENT AREA -->
  <div class="content-box">
    <article id="apexViewer"><em>Loading…</em></article>
  </div>

</div>

<!-- Marked.js (Markdown renderer) -->
<script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>

<script>
(function() {
  const RAW_BASE = "https://raw.githubusercontent.com/kAPEXLab/assignment/main/"; // root files
  const viewer = document.getElementById("apexViewer");
  const nav = document.getElementById("apexNav");

  async function loadFile(file, push=true) {
    try {
      viewer.innerHTML = "<em>Loading…</em>";
      const res = await fetch(RAW_BASE + file, { cache: "no-cache" });
      if (!res.ok) throw new Error("Failed to fetch " + file + " (" + res.status + ")");
      const md = await res.text();
      // Render Markdown -> HTML
      viewer.innerHTML = marked.parse(md);
      // Highlight active link
      highlight(file);
      // Persist deep link
      if (push) history.pushState({ file }, "", "#" + file);
      // Scroll to top of content pane
      viewer.scrollTo({ top: 0, behavior: "smooth" });
    } catch (err) {
      viewer.innerHTML = "<p style='color:#b91c1c'><strong>Error:</strong> " + err.message + "</p>";
    }
  }

  function highlight(file) {
    nav.querySelectorAll("a[data-file]").forEach(a => {
      a.classList.toggle("active", a.dataset.file === file);
    });
  }

  nav.addEventListener("click", (e) => {
    const a = e.target.closest("a[data-file]");
    if (!a) return;
    e.preventDefault();
    loadFile(a.dataset.file);
  });

  window.addEventListener("popstate", (e) => {
    const file = (e.state && e.state.file) || (location.hash ? location.hash.slice(1) : "signal.md");
    loadFile(file, false);
  });

  // Initial load
  const initial = location.hash ? location.hash.slice(1) : "signal.md";
  loadFile(initial, false);
})();
</script>

<noscript>
  <p><strong>Note:</strong> JavaScript is required to render the assignment content inline.</p>
</noscript>
