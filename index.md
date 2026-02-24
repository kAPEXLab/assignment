---
title: "KPIT APEX Lab: Linux Assignment Page"
layout: default
---

<style>
/* 0) Use full width: override GitHub Pages theme container */
.wrapper,
.page,
main,
div[role="main"] {
  max-width: none !important;
  width: 100% !important;
  margin: 0 !important;
  padding: 0 !important;
}
body { margin: 0 !important; padding: 0 !important; }

/* 1) Hide theme chrome on THIS page */
.page-header, .site-header, header,
.site-footer, footer,
a.btn[href*="github.com"],
a[href*="github.com"].btn {
  display: none !important;
}

/* 2) Layout: header + 20/80 grid */
#apex-wrap { padding: 16px; }
#apex-title {
  margin: 0 0 14px 0;
  font-size: 1.8rem;
  font-weight: 800;
  color: #0f172a;
}
#apex-grid {
  display: grid;
  grid-template-columns: 20% 80%;
  gap: 16px;
  align-items: start;
}

/* 3) Left Index */
#apex-nav {
  border: 1px solid #e5e7eb;
  border-radius: 10px;
  padding: 12px;
  background: #ffffff;
  height: calc(100vh - 100px);
  overflow-y: auto;
}
#apex-nav h3 {
  font-size: 1.05rem;
  margin: 4px 0 10px 0;
  color: #475569;
}
#apex-nav a {
  display: block;
  padding: 6px 8px;
  margin-bottom: 6px;
  text-decoration: none;
  color: #0f172a;
  border-radius: 8px;
  border: 1px solid transparent;
}
#apex-nav a:hover,
#apex-nav a.active {
  background: #eef2ff;
  border-color: #c7d2fe;
}

/* 4) Right Content */
#apex-content {
  border: 1px solid #e5e7eb;
  border-radius: 10px;
  padding: 16px;
  background: #ffffff;
  min-height: calc(100vh - 100px);
  overflow-y: auto;
}

/* Code blocks */
#apex-content pre {
  background: #0f172a;
  color: #e5e7eb;
  padding: 12px;
  border-radius: 8px;
  overflow-x: auto;
}

@media (max-width: 900px) {
  #apex-grid { grid-template-columns: 1fr; }
  #apex-nav { height: auto; }
  #apex-content { min-height: 60vh; }
}
</style>

<div id="apex-wrap">

  <!-- TOP HEADER -->
  <h1 id="apex-title">KPIT APEX Lab: Linux Assignment Page</h1>

  <!-- 20% / 80% GRID -->
  <div id="apex-grid">

    <!-- LEFT: INDEX (clickable anchors) -->
    <aside id="apex-nav">
      <h3>Index</h3>

      <!-- IMPORTANT: valid anchors (href + data-file) -->
      #signal.mdSignals</a>
      #thread.mdThreads</a>

      <hr>
      <strong>POSIX IPC</strong>
      #posixpipe.mdPipes (Unnamed)</a>
      #posixfifo.mdFIFOs (Named Pipes)</a>
      #posixmsgque.mdMessage Queues</a>
      #posixshm.mdShared Memory</a>
    </aside>

    <!-- RIGHT: CONTENT -->
    <main id="apex-content">
      <article id="apex-viewer"><em>Loading…</em></article>
    </main>

  </div>
</div>

<!-- Load Marked.js correctly (src attribute is essential) -->
https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>

<script>
(function () {
  const RAW = "https://raw.githubusercontent.com/kAPEXLab/assignment/main/"; // repo root
  const nav = document.getElementById("apex-nav");
  const viewer = document.getElementById("apex-viewer");

  async function load(file, push = true) {
    viewer.innerHTML = "<em>Loading…</em>";
    try {
      const res = await fetch(RAW + file, { cache: "no-cache" });
      if (!res.ok) throw new Error("Failed to fetch " + file + " (" + res.status + ")");
      const md = await res.text();
      viewer.innerHTML = marked.parse(md);

      // highlight current entry
      nav.querySelectorAll("a[data-file]").forEach(a =>
        a.classList.toggle("active", a.dataset.file === file)
      );

      if (push) history.pushState({ file }, "", "#" + file);
      viewer.scrollTop = 0;
    } catch (e) {
      viewer.innerHTML = "<p style='color:#b91c1c'><strong>ERROR:</strong> " + e.message + "</p>";
    }
  }

  // Left index clicks
  nav.addEventListener("click", (e) => {
    const a = e.target.closest("a[data-file]");
    if (!a) return;
    e.preventDefault();
    load(a.dataset.file);
  });

  // Back/forward
  window.addEventListener("popstate", (e) => {
    const file = (e.state && e.state.file) || (location.hash ? location.hash.slice(1) : "signal.md");
    load(file, false);
  });

  // Initial load (default: signal.md)
  const initial = location.hash ? location.hash.slice(1) : "signal.md";
  load(initial, false);
})();
</script>
``
