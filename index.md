<style>
/* 1) MAKE PAGE FULL-WIDTH: override theme container */
.wrapper,
.page,
main,
div[role="main"] {
  max-width: none !important;
  width: 100% !important;
  margin: 0 !important;
  padding: 0 !important;
}

/* Optional: remove any body margin introduced by theme */
body {
  margin: 0 !important;
  padding: 0 !important;
}

/* 2) Hide theme chrome (header/footer/buttons) on THIS PAGE */
.page-header, .site-header, header,
.site-footer, footer,
a.btn[href*="github.com"],
a[href*="github.com"].btn {
  display: none !important;
}

/* 3) Your layout */
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

#apex-wrap { padding: 16px; }

#apex-title {
  margin: 0 0 12px 0;
  font-size: 1.6rem;
  font-weight: 800;
  color: var(--text);
}

/* True edge-to-edge 20/80 grid now that the wrapper is full-width */
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

/* Code blocks */
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
