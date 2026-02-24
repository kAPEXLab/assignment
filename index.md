---
title: KPIT APEX Lab — System Programming Assignments
layout: default
---

<!--
Landing page:
- Heading on top
- Index directly below heading (left 20%)
- Content on right (80%)
- Hide theme chrome (logo, "View the Project on GitHub", "maintained by ...") on THIS page only
- All assignment .md files remain in repo root
-->

<style>
/* ===== Hide default theme chrome on this page (jekyll-theme-minimal) ===== */
.page-header,            /* top banner with project name/tagline */
.site-footer,            /* footer with 'maintained by' text */
a.btn[href*="github.com"]/* "View the Project on GitHub" button */ {
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
  --text-hover: #111827;
}

body { margin: 0; padding: 0; }

/* Container for heading + two-column area below it */
.page-wrap {
  padding: 16px;
}

/* Heading styling (stays visible, above the index) */
.page-title {
  margin: 0 0 12px 0;
  font-size: 1.6rem;
  font-weight: 700;
  color: #0f172a;
}

/* Two-column grid directly BELOW the heading */
.main-grid {
  display: grid;
  grid-template-columns: var(--left) var(--right);
  gap: var(--gap);
  align-items: start;
}

/* Left index (sidebar) */
.sidebar {
  position: sticky;
  top: 10px;
  height: calc(100vh - 80px);
  border: 1px solid var(--border);
  border-radius: 10px;
  padding: 12px;
  background: var(--bg);
  overflow-y: auto;
}

.sidebar h3 {
  margin: 2px 0 10px 0;
  font-size: 1.05rem;
}

.sidebar a {
  display: block;
  padding: 6px 8px;
  margin-bottom: 6px;
  color: var(--text);
  text-decoration: none;
  border-radius: 8px;
  border: 1px solid transparent;
}

.sidebar a:hover,
.sidebar a.active {
  background: #eef2ff;
  border-color: #c7d2fe;
  color: var(--text-hover);
}

/* Right content area */
.content-box {
  border: 1px solid var(--border);
  border-radius: 10px;
  padding: 16px;
  background: var(--bg);
  min-height: calc(100vh - 80px);
  overflow-y: auto;
}

/* Responsive: stack on small screens */
@media (max-width: 900px) {
  .main-grid { grid-template-columns: 1fr; }
  .sidebar { position: relative; height: auto; }
  .content-box { min-height: 60vh; }
}
</style>

<div class="page-wrap">
  <!-- Top heading (kept) -->
  <h1 class="page-title">KPIT APEX Lab — System Programming Assignments</h1>

  <!-- Two-column area directly under the heading -->
  <div class="main-grid">
    <!-- LEFT: Index (20%) -->
    <aside class="sidebar" id="apexNav">
      <h3>Index</h3>
      #signal.mdSignals</a>
      #thread.mdThreads</a>
      <hr>
      <strong>POSIX IPC</strong>
      #posixpipe.mdPipes (Unnamed)</a>
      #posixfifo.mdFIFOs (Named Pipes)</a>
      #posixmsgque.mdMessage Queues</a>
      #posixshm.mdShared Memory</a>
    </aside>

    <!-- RIGHT: Content (80%) -->
    <main class="content-box">
      <article id="apexViewer"><em>Loading…</em></article>
    </main>
  </div>
</div>

<!-- Markdown renderer -->
<script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>

<script>
/* Client-side loader: fetches and renders root-level .md files into the right pane */
(function () {
  const RAW_BASE = "https://raw.githubusercontent.com/kAPEXLab/assignment/main/"; // root of repo
  const nav = document.getElementById("apexNav");
  const viewer = document.getElementById("apexViewer");

  async function loadFile(file, push = true) {
    try {
      viewer.innerHTML = "<em>Loading…</em>";
      const res = await fetch(RAW_BASE + file, { cache: "no-cache" });
      if (!res.ok) throw new Error("Failed to fetch " + file + " (" + res.status + ")");
      const md = await res.text();

      // Render Markdown
      viewer.innerHTML = marked.parse(md);

      // Highlight active link
      highlight(file);

      // Update URL hash for deep-linking/back-forward
      if (push) history.pushState({ file }, "", "#" + file);

      // Ensure we see top of the new content
      viewer.scrollTo({ top: 0, behavior: "smooth" });
    } catch (e) {
      viewer.innerHTML = "<p style='color:#b91c1c'><strong>Error:</strong> " + e.message + "</p>";
    }
  }

  function highlight(file) {
    nav.querySelectorAll("a[data-file]").forEach(a => {
      a.classList.toggle("active", a.dataset.file === file);
    });
  }

  // Handle clicks on the index
  nav.addEventListener("click", (e) => {
    const a = e.target.closest("a[data-file]");
    if (!a) return;
    e.preventDefault();
    loadFile(a.dataset.file);
  });

  // Support browser back/forward
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
