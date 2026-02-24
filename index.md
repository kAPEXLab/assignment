---
title: "KPIT APEX Lab Linux Assignment Page"
layout: default
---

<!--
Requirements:
- Top header: "KPIT APEX Lab: Linux Assignment Page"
- Below header: 20% index (left) + 80% content (right)
- Render root-level .md files on the right
- Remove theme logo / "View on GitHub" / footer on THIS PAGE ONLY
- Keep all files in repo root
-->

<style>
/* ===== Hide theme chrome on this page (jekyll-theme-minimal and similar) ===== */
.page-header, .site-header, header,
.site-footer, footer,
a.btn[href*="github.com"],       /* "View the Project on GitHub" button */
a[href*="github.com"].btn        /* some themes use .btn class */
{ display: none !important; }

/* ===== Layout ===== */
:root {
  --left: 20%;
  --right: 80%;
  --gap: 14px;
  --border: #e5e7eb;
  --bg: #ffffff;
  --text: #0f172a;
  --text-muted: #475569;
}

body { margin: 0; padding: 0; }

#apex-wrap { padding: 16px; }

/* Top header */
#apex-title {
  margin: 0 0 12px 0;
  font-size: 1.6rem;
  font-weight: 800;
  color: var(--text);
}

/* 20/80 grid under the header */
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

/* Code blocks */
#apex-content pre, #apex-content code {
  font-family: ui-monospace, Menlo, Consolas, monospace;
}
#apex-content pre {
  background: #0f172a;
  color: #e5e7eb;
  padding: 12px;
  border-radius: 8px;
  overflow: auto;
}

/* Responsive */
@media (max-width: 900px) {
  #apex-grid { grid-template-columns: 1fr; }
  #apex-nav { position: relative; height: auto; }
  #apex-content { min-height: 60vh; }
}
</style>

<div id="apex-wrap">
  <!-- HEADER -->
  <h1 id="apex-title">KPIT APEX Lab: Linux Assignment Page</h1>

  <!-- TWO-COLUMN SECTION -->
  <div id="apex-grid">
    <!-- LEFT: INDEX (20%) -->
    <aside id="apex-nav">
      <h3>Index</h3>

      <!-- ✅ Correct anchor format: href points to hash, data-file is the filename -->
      <a href="#signal.md"     data-file="signal.md">Signals</a>
      <a href="#thread.md"     data-file="thread.md">Threads</a>

      <hr>
      <strong>POSIX IPC</strong>
      <a href="#posixpipe.md"  data-file="posixpipe.md">Pipes (Unnamed)</a>
      <a href="#posixfifo.md"  data-file="posixfifo.md">FIFOs (Named Pipes)</a>
      <a href="#posixshm.md"   data-file="posixshm.md">Shared Memory</a>
      <a href="#posixmsgque.md"data-file="posixmsgque.md">Message Queues</a>
    </aside>

    <!-- RIGHT: CONTENT (80%) -->
    <main id="apex-content">
      <article id="apex-viewer"><em>Loading…</em></article>
    </main>
  </div>
</div>

<!-- ✅ Proper script tag with src attribute -->
<script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>

<script>
/* Loader: fetch & render root-level Markdown files into the right pane */
(function () {
  const RAW = "https://raw.githubusercontent.com/kAPEXLab/assignment/main/"; // root of repo
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
      viewer.scrollTop = 0;
    } catch (e) {
      viewer.innerHTML = "<p style='color:#b91c1c'><strong>Error:</strong> " + e.message + "</p>";
    }
  }

  function highlight(file) {
    nav.querySelectorAll("a[data-file]").forEach(a => {
      a.classList.toggle("active", a.dataset.file === file);
    });
  }

  // Clicks on the index
  nav.addEventListener("click", (e) => {
    const a = e.target.closest("a[data-file]");
    if (!a) return;
    e.preventDefault();
    load(a.dataset.file);
  });

  // Back/forward navigation
  window.addEventListener("popstate", (e) => {
    const file = (e.state && e.state.file) || (location.hash ? location.hash.slice(1) : "signal.md");
    load(file, false);
  });

  // Initial content
  const initial = location.hash ? location.hash.slice(1) : "signal.md";
  load(initial, false);
})();
</script>

<noscript>
  <p><strong>Note:</strong> JavaScript is required to render the assignment content inline.</p>
</noscript>
