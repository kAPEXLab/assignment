---
title: KPIT APEX Lab: Linux Assignment Page
layout: default
---

<!--
Landing page EXACTLY as required:
- Top header: "KPIT APEX Lab: Linux Assignment Page"
- Below header: 20% index (left) + 80% content (right)
- No logo, no "View the Project on GitHub", no footer/maintainer note
- All assignment .md files stay in the repository root
-->

<style>
/* ===== Remove ALL theme chrome on this page (jekyll-theme-minimal or similar) ===== */
.page-header, .site-header, header,
.site-footer, footer,
a.btn[href*="github.com"], /* "View the Project on GitHub" button */
a[href*="github.com"][class*="btn"] {
  display: none !important;
}

/* ===== Page layout ===== */
:root {
  --left: 20%;
  --right: 80%;
  --gap: 14px;
  --border: #e5e7eb;
  --bg: #ffffff;
  --text: #0f172a;
  --text-muted: #475569;
  --text-hover: #0b1220;
}

body { margin: 0; padding: 0; }

#apex-wrap { padding: 16px; }

/* Top header you asked for */
#apex-title {
  margin: 0 0 12px 0;
  font-size: 1.6rem;
  font-weight: 800;
  color: var(--text);
}

/* Grid below the header: 20% / 80% */
#apex-grid {
  display: grid;
  grid-template-columns: minmax(180px, var(--left)) var(--right);
  gap: var(--gap);
  align-items: start;
}

/* Left index */
#apex-nav {
  position: sticky;
  top: 10px;
  height: calc(100vh - 80px);
  border: 1px solid var(--border);
  border-radius: 10px;
  padding: 12px;
  background: var(--bg);
  overflow-y: auto;
}

#apex-nav h3 {
  margin: 2px 0 10px 0;
  font-size: 1.05rem;
  color: var(--text-muted);
}

#apex-nav a {
  display: block;
  padding: 6px 8px;
  margin-bottom: 6px;
  color: var(--text);
  text-decoration: none;
  border-radius: 8px;
  border: 1px solid transparent;
}

#apex-nav a:hover,
#apex-nav a.active {
  background: #eef2ff;
  border-color: #c7d2fe;
  color: var(--text-hover);
}

/* Right content */
#apex-content {
  border: 1px solid var(--border);
  border-radius: 10px;
  background: var(--bg);
  min-height: calc(100vh - 80px);
  overflow: auto;
  padding: 16px;
}

/* Make code blocks pleasant */
#apex-content pre {
  background: #0f172a;
  color: #e5e7eb;
  padding: 12px;
  border-radius: 8px;
  overflow: auto;
}

/* Headings spacing inside content */
#apex-content h1, #apex-content h2, #apex-content h3 {
  margin-top: 1rem;
}

/* Responsive: stack on small screens */
@media (max-width: 900px) {
  #apex-grid { grid-template-columns: 1fr; }
  #apex-nav { position: relative; height: auto; }
  #apex-content { min-height: 60vh; }
}
</style>

<div id="apex-wrap">
  <!-- TOP HEADER (only visible header) -->
  <h1 id="apex-title">KPIT APEX Lab - Linux Assignment Page</h1>

  <!-- TWO-COLUMN LAYOUT BELOW THE HEADER -->
  <div id="apex-grid">
    <!-- LEFT: INDEX (20%) -->
    <aside id="apex-nav">
      <h3>Index</h3>
      <!-- Update this list to match the .md files you keep in root -->
      #signal.mdSignals</a>
      #thread.mdThreads</a>
      <hr>
      <strong>POSIX IPC</strong>
      #posixpipe.mdPipes (Unnamed)</a>
      #posixfifo.mdFIFOs (Named Pipes)</a>
      #posixshm.mdShared Memory</a>
      #posixmsgque.mdMessage Queues</a>
    </aside>

    <!-- RIGHT: CONTENT (80%) -->
    <main id="apex-content">
      <article id="apex-viewer"><em>Loading…</em></article>
    </main>
  </div>
</div>

<!-- Markdown renderer (MIT) -->
<script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>

<script>
/* Client-side loader: fetches & renders ROOT .md files into the right pane */
(function () {
  const RAW = "https://raw.githubusercontent.com/kAPEXLab/assignment/main/"; // root of your repo
  const nav = document.getElementById("apex-nav");
  const viewer = document.getElementById("apex-viewer");

  async function load(file, push = true) {
    viewer.innerHTML = "<em>Loading…</em>";
    try {
      const res = await fetch(RAW + file, { cache: "no-cache" });
      if (!res.ok) throw new Error("Failed to fetch " + file + " (" + res.status + ")");
      const md = await res.text();
      viewer.innerHTML = marked.parse(md);
      highlight(file);
      if (push) history.pushState({ file }, "", "#" + file);
      viewer.scrollTo({ top: 0, behavior: "instant" });
    } catch (e) {
      viewer.innerHTML = "<p style='color:#b91c1c'><strong>Error:</strong> " + e.message + "</p>";
    }
  }

  function highlight(file) {
    nav.querySelectorAll("a[data-file]").forEach(a => {
      a.classList.toggle("active", a.dataset.file === file);
    });
  }

  // Link clicks in the index
  nav.addEventListener("click", (e) => {
    const a = e.target.closest("a[data-file]");
    if (!a) return;
    e.preventDefault();
    load(a.dataset.file);
  });

  // Back/forward support
  windower("popstate", (e) => {
    const file = (e.state && e.state.file) || (location.hash ? location.hash.slice(1) : "signal.md");
    load(file, false);
  });

  // Initial load (default to signal.md if no hash)
  const initial = location.hash ? location.hash.slice(1) : "signal.md";
  load(initial, false);
})();
</script>

<noscript>
  <p><strong>Note:</strong> Enable JavaScript to view assignment content.</p>
</noscript>
