---
title: Assignments
layout: default
---

<!-- HIDE GitHub Pages default header/footer -->
<style>
/* Hide theme header (project title + tagline) */
header.site-header,
header,
.site-header {
  display: none !important;
}

/* Hide “View the Project on GitHub” button */
a.github-button,
a.btn,
header .btn,
header a[href*="github.com"] {
  display: none !important;
}

/* Hide footer (“This project is maintained by…”) */
footer,
.site-footer,
.footer {
  display: none !important;
}

/* BODY LAYOUT */
:root {
  --left: 20%;
  --right: 80%;
  --border: #e5e7eb;
  --bg: #ffffff;
  --text: #0f172a;
}

body {
  margin: 0;
  padding: 0;
}

.main-container {
  display: grid;
  grid-template-columns: var(--left) var(--right);
  gap: 10px;
  padding: 10px;
}

/* LEFT SIDEBAR */
.sidebar {
  position: sticky;
  top: 0;
  height: 100vh;
  border: 1px solid var(--border);
  border-radius: 8px;
  padding: 12px;
  background: var(--bg);
  overflow-y: auto;
}

.sidebar a {
  display: block;
  padding: 6px 8px;
  margin-bottom: 6px;
  color: var(--text);
  text-decoration: none;
  border-radius: 6px;
}

.sidebar a:hover,
.sidebar a.active {
  background: #eef2ff;
  border: 1px solid #c7d2fe;
}

/* RIGHT CONTENT AREA */
