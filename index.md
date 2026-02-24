---
title: "KPIT APEX Lab: Linux Assignment Page"
layout: default
---

<style>
/* =======================
   REMOVE GITHUB THEME WRAPPER
   ======================= */
.wrapper,
.page,
main,
div[role="main"] {
  max-width: none !important;
  width: 100% !important;
  margin: 0 !important;
  padding: 0 !important;
}

/* Remove any default margin */
body {
  margin: 0 !important;
  padding: 0 !important;
}

/* Hide GitHub Pages default chrome */
.page-header,
.site-header,
header,
.site-footer,
footer,
a.btn[href*="github.com"],
a[href*="github.com"].btn {
  display: none !important;
}

/* =======================
   LAYOUT GRID (20% / 80%)
   ======================= */
#apex-wrap {
  padding: 16px;
}

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
}

/* =======================
   LEFT SIDEBAR (INDEX)
   ======================= */
#apex-nav {
  border: 1px solid #e5e7eb;
  border-radius: 10px;
  padding: 12px;
  background: #ffffff;
  height: calc(100vh - 100px);
  overflow-y: auto;
}

#apex-nav h3 {
  font-size: 1.1rem;
  margin-top: 0;
}

#apex-nav a {
  display: block;
  padding: 6px 8px;
  margin-bottom: 6px;
  text-decoration: none;
  color: #0f172a;
  border-radius: 6px;
}

#apex-nav a:hover,
#apex-nav a.active {
  background: #eef2ff;
  border: 1px solid #c7d2fe;
}

/* =======================
   RIGHT CONTENT BOX
   ======================= */
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

@media(max-width:900px){
  #apex-grid { grid-template-columns: 1fr; }
  #apex-nav { height: auto; }
}
</style>

<div id="apex-wrap">

<h1 id="apex-title">KPIT APEX Lab: Linux Assignment Page</h1>

<div id="apex-grid">

  <!-- LEFT INDEX -->
  <aside id="apex-nav">
    <h3>Index</h3>

    <!-- Must be EXACT anchor format: href="#file.md" + data-file="file.md" -->
    #signal.mdSignals</a>
    #thread.mdThreads</a>

    <hr>
    <strong>POSIX IPC</strong>
    #posixpipe.mdPipes (Unnamed)</a>
    #posixfifo.mdFIFOs (Named Pipes)</a>
    #posixmsgque.mdMessage Queues</a>
    #posixshm.mdShared Memory</a>
  </aside>

  <!-- RIGHT CONTENT AREA -->
  <main id="apex-content">
    <article id="apex-viewer"><em>Loading…</em></article>
  </main>

</div>
</div>

<!-- MARKDOWN RENDERER -->
https://cdn.jsdelivr.net/npm/marked/marked.min.js</script>

<script>
(function() {

  const RAW = "https://raw.githubusercontent.com/kAPEXLab/assignment/main/";
  const nav = document.getElementById("apex-nav");
  const viewer = document.getElementById("apex-viewer");

  async function load(file, push = true) {
    viewer.innerHTML = "<em>Loading…</em>";
    try {
      const res = await fetch(RAW + file, { cache: "no-cache" });
      if (!res.ok) throw new Error("Cannot load " + file);
      const md = await res.text();
      viewer.innerHTML = marked.parse(md);

      // highlight active link
      nav.querySelectorAll("a[data-file]").forEach(a =>
        a.classList.toggle("active", a.dataset.file === file)
      );

      if (push) history.pushState({file}, "", "#" + file);
      viewer.scrollTop = 0;

    } catch (e) {
      viewer.innerHTML = "<p style='color:red'>ERROR: " + e.message + "</p>";
    }
  }

  // Handle clicks
  nav.addEventListener("click", e => {
    const a = e.target.closest("a[data-file]");
    if (!a) return;
    e.preventDefault();
    load(a.dataset.file);
  });

  // Browser back/forward
  window.addEventListener("popstate", e => {
    const file = (e.state && e.state.file) || location.hash.slice(1) || "signal.md";
    load(file, false);
  });

  // Initial load
  const initial = location.hash.slice(1) || "signal.md";
  load(initial, false);

})();
</script>
