<!DOCTYPE html>
<html lang="th">
<head>
<meta charset="UTF-8">
<title>ระบบติดตามงาน & ให้คุณให้โทษ</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="theme-color" content="#1a1a1a">
<meta name="mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<meta name="apple-mobile-web-app-title" content="ติดตามงาน">
<link rel="icon" href="icon-192.png">
<link rel="apple-touch-icon" href="icon-192.png">
<link rel="manifest" href="manifest.json">
<style>
*{box-sizing:border-box;font-family:'Segoe UI','Prompt',sans-serif;margin:0;padding:0;}
:root{
  --primary:#2b2b2b;--primary-soft:#e9e9ea;--primary-dark:#161616;
  --sidebar:#1a1a1a;--sidebar-hover:#262626;--sidebar-active:#333333;
  --accent:#ff8c42;--accent-dark:#e07030;
  --success:#16a34a;--success-soft:#f0fdf4;
  --danger:#dc2626;--danger-soft:#fef2f2;
  --warning:#d97706;--warning-soft:#fffbeb;
  --gold:#eab308;--gold-soft:#fefce8;
  --bg:#f1f1f1;--surface:#ffffff;--surface2:#f9f9f9;
  --border:#e2e2e2;--text:#1c1c1c;--text2:#6b6b6b;--text3:#3a3a3a;
  --radius:14px;--radius-sm:8px;--shadow:0 8px 24px rgba(0,0,0,0.08);
  --shadow-md:0 12px 32px rgba(0,0,0,0.16);
}
body{background:var(--bg);color:var(--text);min-height:100vh;font-size:14px;}
header{
  background:linear-gradient(90deg,#161616,#222222,#2c2c2c);
  color:white;padding:12px 20px;display:flex;align-items:center;justify-content:space-between;
  box-shadow:0 2px 12px rgba(0,0,0,0.4);position:sticky;top:0;z-index:100;
}
.header-left{display:flex;align-items:center;gap:12px;}
.header-logo{width:38px;height:38px;border-radius:10px;background:#ffffff14;display:flex;align-items:center;justify-content:center;font-size:20px;border:1px solid #ffffff22;}
.header-title{font-size:18px;font-weight:700;letter-spacing:-0.02em;}
.header-sub{font-size:11px;opacity:0.65;margin-top:1px;}
.header-right{display:flex;align-items:center;gap:8px;}
.header-badge{background:rgba(255,255,255,0.12);border:1px solid rgba(255,255,255,0.2);border-radius:999px;padding:4px 12px;font-size:12px;display:flex;align-items:center;gap:6px;}
.badge-dot{width:8px;height:8px;border-radius:50%;background:#4ade80;}
.badge-dot.warn{background:#fb923c;}

.layout{display:flex;height:calc(100vh - 62px);}
.sidebar{width:220px;flex-shrink:0;background:var(--sidebar);color:#d4d4d4;display:flex;flex-direction:column;overflow:hidden;box-shadow:4px 0 16px rgba(0,0,0,0.3);}
.sidebar-inner{flex:1;overflow-y:auto;padding:12px 10px;}
.sidebar-inner::-webkit-scrollbar{width:4px;}
.sidebar-inner::-webkit-scrollbar-thumb{background:#ffffff22;border-radius:2px;}
.nav-group{margin-bottom:16px;}
.nav-group-label{font-size:10px;text-transform:uppercase;letter-spacing:0.1em;opacity:0.45;padding:0 8px;margin-bottom:6px;}
.nav-btn{width:100%;text-align:left;padding:9px 12px;border-radius:10px;border:none;background:transparent;color:#b8b8b8;display:flex;align-items:center;gap:10px;font-size:13px;cursor:pointer;transition:all 0.15s;}
.nav-btn .icon{width:20px;text-align:center;font-size:15px;flex-shrink:0;}
.nav-btn .label{flex:1;}
.nav-btn .nbadge{background:#ef4444;color:white;font-size:10px;font-weight:700;padding:1px 6px;border-radius:999px;min-width:18px;text-align:center;}
.nav-btn.active{background:var(--sidebar-active);color:white;box-shadow:0 3px 10px rgba(0,0,0,0.3);}
.nav-btn:hover:not(.active){background:var(--sidebar-hover);color:white;}
.sidebar-footer{padding:10px 12px;border-top:1px solid #ffffff11;font-size:10px;opacity:0.5;}

.main{flex:1;overflow-y:auto;padding:18px 20px;}
.section{display:none;animation:fadeIn 0.2s ease;}
.section.active{display:block;}
@keyframes fadeIn{from{opacity:0;transform:translateY(6px);}to{opacity:1;transform:translateY(0);}}

.page-header{margin-bottom:16px;}
.page-title{font-size:20px;font-weight:700;color:var(--primary);display:flex;align-items:center;gap:8px;}
.page-sub{font-size:12px;color:var(--text2);margin-top:3px;}

.card{background:var(--surface);border-radius:var(--radius);padding:18px 20px;border:1px solid var(--border);box-shadow:var(--shadow);}
.card-title{font-size:14px;font-weight:600;color:var(--text3);margin-bottom:12px;display:flex;align-items:center;gap:6px;}

.stats-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(190px,1fr));gap:12px;margin-bottom:16px;}
.stat-card{background:var(--surface);border-radius:var(--radius);padding:16px 18px;border:1px solid var(--border);box-shadow:var(--shadow);display:flex;align-items:center;gap:14px;transition:transform .15s,box-shadow .15s;}
.stat-card:hover{transform:translateY(-2px);box-shadow:var(--shadow-md);}
.stat-icon{width:44px;height:44px;border-radius:12px;display:flex;align-items:center;justify-content:center;font-size:20px;flex-shrink:0;}
.stat-label{font-size:11px;color:var(--text2);text-transform:uppercase;letter-spacing:0.04em;}
.stat-value{font-size:22px;font-weight:700;color:var(--text);margin-top:2px;line-height:1.1;}

.toolbar{display:flex;gap:8px;flex-wrap:wrap;align-items:center;margin-bottom:12px;}
.form-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(220px,1fr));gap:12px;}
.form-row{display:flex;flex-direction:column;gap:4px;}
label{font-size:12px;color:var(--text2);font-weight:500;}
input,select,textarea{padding:9px 11px;border-radius:var(--radius-sm);border:1px solid #c5ced9;background:var(--surface2);color:var(--text);font-size:13px;transition:border .15s,box-shadow .15s;width:100%;}
input:focus,select:focus,textarea:focus{outline:none;border-color:var(--primary);box-shadow:0 0 0 3px rgba(40,40,40,0.15);background:white;}
textarea{resize:vertical;min-height:70px;font-family:inherit;}
input:disabled,select:disabled{opacity:.6;cursor:not-allowed;}

button{padding:8px 16px;border:none;border-radius:999px;cursor:pointer;font-size:13px;display:inline-flex;align-items:center;gap:6px;transition:all .15s;font-family:inherit;font-weight:500;}
.btn-primary{background:var(--primary);color:white;}
.btn-primary:hover{background:var(--primary-dark);box-shadow:0 4px 12px rgba(0,0,0,.35);transform:translateY(-1px);}
.btn-orange{background:var(--accent);color:white;}
.btn-orange:hover{background:var(--accent-dark);box-shadow:0 4px 12px rgba(255,140,66,.35);transform:translateY(-1px);}
.btn-success{background:var(--success);color:white;}
.btn-success:hover{background:#15803d;transform:translateY(-1px);}
.btn-danger{background:var(--danger);color:white;}
.btn-danger:hover{background:#b91c1c;transform:translateY(-1px);}
.btn-gold{background:var(--gold);color:white;}
.btn-gold:hover{background:#ca8a04;transform:translateY(-1px);}
.btn-outline{background:white;border:1.5px solid var(--primary);color:var(--primary);}
.btn-outline:hover{background:var(--primary-soft);}
.btn-ghost{background:transparent;color:var(--text2);border:1px solid var(--border);}
.btn-ghost:hover{background:var(--surface2);color:var(--text);}
.btn-sm{padding:5px 12px;font-size:12px;}
.btn-xs{padding:3px 9px;font-size:11px;}

.table-wrap{overflow-x:auto;border-radius:var(--radius-sm);border:1px solid var(--border);}
table{width:100%;border-collapse:collapse;}
th{background:#edf2f7;color:var(--text3);font-weight:600;font-size:12px;padding:10px 12px;text-align:left;white-space:nowrap;border-bottom:1px solid var(--border);}
td{padding:9px 12px;font-size:13px;border-bottom:1px solid #f0f3f8;vertical-align:middle;}
tr:last-child td{border-bottom:none;}
tr:hover td{background:#f7f9fc;}
.text-right{text-align:right;}
.text-center{text-align:center;}
.text-muted{color:var(--text2);}

.hint{font-size:11px;margin-top:4px;min-height:16px;}
.hint-warn{color:var(--warning);}
.hint-ok{color:var(--success);}
.hint-err{color:var(--danger);}

.tag{display:inline-block;padding:2px 9px;border-radius:999px;font-size:11px;font-weight:600;white-space:nowrap;}
.tag-pending{background:#f3f4f6;color:#4b5563;border:1px solid #e5e7eb;}
.tag-progress{background:#eff6ff;color:#1d4ed8;border:1px solid #bfdbfe;}
.tag-done{background:#f0fdf4;color:#166534;border:1px solid #bbf7d0;}
.tag-late{background:#fef2f2;color:#991b1b;border:1px solid #fecaca;}
.tag-high{background:#fef2f2;color:#b91c1c;border:1px solid #fecaca;}
.tag-mid{background:#fffbeb;color:#b45309;border:1px solid #fde68a;}
.tag-low{background:#f0fdf4;color:#15803d;border:1px solid #bbf7d0;}

/* TASK CARDS (kanban style) */
.kanban{display:grid;grid-template-columns:repeat(4,1fr);gap:14px;}
.kanban-col{background:#eeeeee;border-radius:14px;padding:12px;min-height:200px;}
.kanban-col-title{font-size:13px;font-weight:700;color:var(--text3);margin-bottom:10px;display:flex;justify-content:space-between;align-items:center;}
.kanban-col-count{background:#dcdcdc;border-radius:999px;padding:1px 8px;font-size:11px;}
.task-card{background:white;border-radius:10px;padding:12px;margin-bottom:8px;border:1px solid var(--border);box-shadow:0 2px 6px rgba(15,23,42,0.06);transition:box-shadow .15s,transform .15s;cursor:pointer;}
.task-card:hover{box-shadow:0 6px 16px rgba(15,23,42,0.14);transform:translateY(-1px);}
.task-card-title{font-weight:600;font-size:13px;margin-bottom:6px;color:var(--text);}
.task-card-meta{font-size:11px;color:var(--text2);display:flex;flex-wrap:wrap;gap:6px;align-items:center;margin-top:6px;}
.task-card-avatar{display:inline-flex;align-items:center;gap:4px;background:var(--primary-soft);color:var(--primary);border-radius:999px;padding:2px 8px;font-size:11px;font-weight:600;}
.task-card.overdue{border-left:3px solid var(--danger);}
.task-card.due-soon{border-left:3px solid var(--warning);}

/* SCORE BOARD */
.rank-card{display:flex;align-items:center;gap:14px;background:var(--surface);border-radius:12px;padding:12px 16px;margin-bottom:8px;border:1px solid var(--border);transition:box-shadow .15s;}
.rank-card:hover{box-shadow:var(--shadow);}
.rank-num{font-size:18px;font-weight:800;width:32px;text-align:center;color:var(--text2);}
.rank-num.gold{color:#eab308;}
.rank-num.silver{color:#94a3b8;}
.rank-num.bronze{color:#c2703a;}
.rank-avatar{width:40px;height:40px;border-radius:50%;background:linear-gradient(135deg,#2b2b2b,#444444);color:white;display:flex;align-items:center;justify-content:center;font-weight:700;font-size:15px;flex-shrink:0;}
.rank-info{flex:1;min-width:0;}
.rank-name{font-weight:600;font-size:14px;}
.rank-meta{font-size:11px;color:var(--text2);}
.rank-score{font-size:20px;font-weight:800;text-align:right;}
.rank-score.pos{color:var(--success);}
.rank-score.neg{color:var(--danger);}

/* SCORE LOG */
.log-card{background:var(--surface);border:1px solid var(--border);border-radius:10px;padding:12px 14px;margin-bottom:8px;display:flex;justify-content:space-between;align-items:flex-start;gap:12px;}
.log-info{flex:1;}
.log-name{font-weight:600;margin-bottom:2px;}
.log-reason{font-size:12px;color:var(--text2);}
.log-meta{font-size:11px;color:#9ca3af;margin-top:4px;}
.log-points{font-size:18px;font-weight:800;white-space:nowrap;}
.log-points.pos{color:var(--success);}
.log-points.neg{color:var(--danger);}

.divider{border:none;border-top:1px solid var(--border);margin:16px 0;}

.empty-state{padding:40px 20px;text-align:center;color:var(--text2);}
.empty-icon{font-size:40px;margin-bottom:10px;opacity:.5;}
.empty-msg{font-size:13px;}

.filter-row{display:flex;gap:8px;flex-wrap:wrap;align-items:center;margin-bottom:12px;}
.filter-row input,.filter-row select{width:auto;flex:1;min-width:140px;max-width:220px;}

/* TOAST */
#toast-container{position:fixed;bottom:24px;right:24px;z-index:99999;display:flex;flex-direction:column;gap:8px;align-items:flex-end;}
.toast{background:var(--text);color:white;padding:11px 16px;border-radius:10px;font-size:13px;max-width:300px;display:flex;align-items:center;gap:10px;animation:toastIn .2s ease;box-shadow:0 8px 24px rgba(15,23,42,0.35);}
.toast.success{background:#15803d;}
.toast.error{background:#b91c1c;}
.toast.warn{background:#b45309;}
.toast .t-close{margin-left:6px;opacity:.7;cursor:pointer;font-size:15px;line-height:1;}
.toast .t-close:hover{opacity:1;}
@keyframes toastIn{from{opacity:0;transform:translateX(20px);}to{opacity:1;transform:translateX(0);}}

/* CONFIRM */
.confirm-overlay{position:fixed;inset:0;background:rgba(15,23,42,0.5);z-index:9998;display:none;align-items:center;justify-content:center;}
.confirm-box{background:white;border-radius:16px;padding:22px 24px;min-width:300px;max-width:400px;box-shadow:0 20px 50px rgba(15,23,42,0.5);animation:popIn .18s ease-out;}
.confirm-title{font-size:16px;font-weight:700;margin-bottom:8px;}
.confirm-msg{font-size:13px;color:var(--text2);margin-bottom:18px;line-height:1.6;}
.confirm-footer{display:flex;justify-content:flex-end;gap:8px;}
@keyframes popIn{from{transform:scale(0.93);opacity:0;}to{transform:scale(1);opacity:1;}}

/* POPUP */
.popup-overlay{position:fixed;inset:0;background:rgba(15,23,42,0.5);z-index:9997;display:none;align-items:center;justify-content:center;padding:16px;}
.popup-card{background:white;border-radius:16px;padding:20px;width:min(560px,95vw);max-height:90vh;overflow-y:auto;box-shadow:0 20px 50px rgba(15,23,42,.5);animation:popIn .18s ease-out;}
.popup-title{font-size:16px;font-weight:700;color:var(--primary);margin-bottom:12px;display:flex;align-items:center;gap:8px;}
.popup-footer{display:flex;justify-content:flex-end;gap:8px;margin-top:14px;padding-top:12px;border-top:1px solid var(--border);}

.score-toggle{display:flex;gap:6px;background:#eeeeee;border-radius:999px;padding:4px;width:fit-content;margin-bottom:14px;}
.score-toggle button{border-radius:999px;}
.score-toggle .stog-inactive{background:transparent;color:var(--text2);}
.score-toggle .stog-active.give{background:var(--success);color:white;}
.score-toggle .stog-active.take{background:var(--danger);color:white;}

@media(max-width:900px){ .kanban{grid-template-columns:1fr;} }
@media(max-width:760px){
  .layout{flex-direction:column-reverse;}
  .sidebar{width:100%;flex-direction:row;height:56px;flex-shrink:0;overflow:visible;}
  .sidebar-inner{display:flex;flex-direction:row;overflow-x:auto;padding:4px 6px;gap:2px;scrollbar-width:none;}
  .sidebar-inner::-webkit-scrollbar{display:none;}
  .nav-group{margin:0;display:flex;gap:2px;}
  .nav-group-label,.sidebar-footer{display:none;}
  .nav-btn{flex-direction:column;gap:2px;padding:6px 10px;border-radius:8px;font-size:10px;min-width:56px;}
  .nav-btn .icon{width:auto;font-size:18px;}
  .main{padding:12px 14px;}
  .stats-grid{grid-template-columns:repeat(2,1fr);}
  .form-grid{grid-template-columns:1fr;}
}
.main::-webkit-scrollbar{width:6px;}
.main::-webkit-scrollbar-thumb{background:#c5ced9;border-radius:3px;}
@media print{ .no-print{display:none!important;} }

/* ── ICON SYSTEM (inline SVG via mask, inherits color) ── */
.ic{display:inline-block;width:1em;height:1em;background-color:currentColor;-webkit-mask-size:contain;mask-size:contain;-webkit-mask-repeat:no-repeat;mask-repeat:no-repeat;-webkit-mask-position:center;mask-position:center;vertical-align:-0.14em;flex-shrink:0;}
.ic-lg{width:1.3em;height:1.3em;}
.ic-target{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Ccircle cx='12' cy='12' r='9'/%3E%3Ccircle cx='12' cy='12' r='5'/%3E%3Ccircle cx='12' cy='12' r='1.4' fill='black'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Ccircle cx='12' cy='12' r='9'/%3E%3Ccircle cx='12' cy='12' r='5'/%3E%3Ccircle cx='12' cy='12' r='1.4' fill='black'/%3E%3C/svg%3E");}
.ic-grid{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Crect x='3' y='3' width='7' height='7' rx='1'/%3E%3Crect x='14' y='3' width='7' height='7' rx='1'/%3E%3Crect x='3' y='14' width='7' height='7' rx='1'/%3E%3Crect x='14' y='14' width='7' height='7' rx='1'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Crect x='3' y='3' width='7' height='7' rx='1'/%3E%3Crect x='14' y='3' width='7' height='7' rx='1'/%3E%3Crect x='3' y='14' width='7' height='7' rx='1'/%3E%3Crect x='14' y='14' width='7' height='7' rx='1'/%3E%3C/svg%3E");}
.ic-plus{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2'%3E%3Cline x1='12' y1='5' x2='12' y2='19'/%3E%3Cline x1='5' y1='12' x2='19' y2='12'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2'%3E%3Cline x1='12' y1='5' x2='12' y2='19'/%3E%3Cline x1='5' y1='12' x2='19' y2='12'/%3E%3C/svg%3E");}
.ic-clock{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Ccircle cx='12' cy='12' r='9'/%3E%3Cpath d='M12 7v5l3.5 2'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Ccircle cx='12' cy='12' r='9'/%3E%3Cpath d='M12 7v5l3.5 2'/%3E%3C/svg%3E");}
.ic-star{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='black'%3E%3Cpath d='M12 2.5l2.9 6.1 6.6.8-4.9 4.5 1.3 6.6L12 17.6l-5.9 2.9 1.3-6.6L2.5 9.4l6.6-.8z'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='black'%3E%3Cpath d='M12 2.5l2.9 6.1 6.6.8-4.9 4.5 1.3 6.6L12 17.6l-5.9 2.9 1.3-6.6L2.5 9.4l6.6-.8z'/%3E%3C/svg%3E");}
.ic-trophy{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.7'%3E%3Cpath d='M7 4h10v4a5 5 0 0 1-10 0V4z'/%3E%3Cpath d='M7 5H4a2 2 0 0 0 2 4'/%3E%3Cpath d='M17 5h3a2 2 0 0 1-2 4'/%3E%3Cpath d='M9 17h6'/%3E%3Cpath d='M12 13v6'/%3E%3Cpath d='M8 21h8'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.7'%3E%3Cpath d='M7 4h10v4a5 5 0 0 1-10 0V4z'/%3E%3Cpath d='M7 5H4a2 2 0 0 0 2 4'/%3E%3Cpath d='M17 5h3a2 2 0 0 1-2 4'/%3E%3Cpath d='M9 17h6'/%3E%3Cpath d='M12 13v6'/%3E%3Cpath d='M8 21h8'/%3E%3C/svg%3E");}
.ic-doc{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M7 3h7l4 4v13a1 1 0 0 1-1 1H7a1 1 0 0 1-1-1V4a1 1 0 0 1 1-1z'/%3E%3Cpath d='M14 3v4h4'/%3E%3Cline x1='8.5' y1='12' x2='15.5' y2='12'/%3E%3Cline x1='8.5' y1='15.5' x2='15.5' y2='15.5'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M7 3h7l4 4v13a1 1 0 0 1-1 1H7a1 1 0 0 1-1-1V4a1 1 0 0 1 1-1z'/%3E%3Cpath d='M14 3v4h4'/%3E%3Cline x1='8.5' y1='12' x2='15.5' y2='12'/%3E%3Cline x1='8.5' y1='15.5' x2='15.5' y2='15.5'/%3E%3C/svg%3E");}
.ic-users{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M16 11a3 3 0 1 0 0-6'/%3E%3Cpath d='M3 20v-1a5 5 0 0 1 5-5h2a5 5 0 0 1 5 5v1'/%3E%3Ccircle cx='9' cy='8' r='3.2'/%3E%3Cpath d='M18 14a4.2 4.2 0 0 1 3 4v2'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M16 11a3 3 0 1 0 0-6'/%3E%3Cpath d='M3 20v-1a5 5 0 0 1 5-5h2a5 5 0 0 1 5 5v1'/%3E%3Ccircle cx='9' cy='8' r='3.2'/%3E%3Cpath d='M18 14a4.2 4.2 0 0 1 3 4v2'/%3E%3C/svg%3E");}
.ic-check{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2.2'%3E%3Cpolyline points='4,13 9,18 20,6'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2.2'%3E%3Cpolyline points='4,13 9,18 20,6'/%3E%3C/svg%3E");}
.ic-x{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2.2'%3E%3Cline x1='5' y1='5' x2='19' y2='19'/%3E%3Cline x1='19' y1='5' x2='5' y2='19'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2.2'%3E%3Cline x1='5' y1='5' x2='19' y2='19'/%3E%3Cline x1='19' y1='5' x2='5' y2='19'/%3E%3C/svg%3E");}
.ic-wrench{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M14.7 6.3a4 4 0 0 0-5.6 5.6L3 18l3 3 6.1-6.1a4 4 0 0 0 5.6-5.6l-2.1 2.1-2.5-.6-.6-2.5z'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M14.7 6.3a4 4 0 0 0-5.6 5.6L3 18l3 3 6.1-6.1a4 4 0 0 0 5.6-5.6l-2.1 2.1-2.5-.6-.6-2.5z'/%3E%3C/svg%3E");}
.ic-hourglass{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M6 3h12'/%3E%3Cpath d='M6 21h12'/%3E%3Cpath d='M7 3c0 4 5 5 5 9s-5 5-5 9'/%3E%3Cpath d='M17 3c0 4-5 5-5 9s5 5 5 9'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M6 3h12'/%3E%3Cpath d='M6 21h12'/%3E%3Cpath d='M7 3c0 4 5 5 5 9s-5 5-5 9'/%3E%3Cpath d='M17 3c0 4-5 5-5 9s5 5 5 9'/%3E%3C/svg%3E");}
.ic-search{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2'%3E%3Ccircle cx='11' cy='11' r='7'/%3E%3Cline x1='21' y1='21' x2='16.2' y2='16.2'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='2'%3E%3Ccircle cx='11' cy='11' r='7'/%3E%3Cline x1='21' y1='21' x2='16.2' y2='16.2'/%3E%3C/svg%3E");}
.ic-save{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M5 4h11l3 3v13a1 1 0 0 1-1 1H5a1 1 0 0 1-1-1V5a1 1 0 0 1 1-1z'/%3E%3Cpath d='M8 4v5h7V4'/%3E%3Crect x='7' y='14' width='10' height='6'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M5 4h11l3 3v13a1 1 0 0 1-1 1H5a1 1 0 0 1-1-1V5a1 1 0 0 1 1-1z'/%3E%3Cpath d='M8 4v5h7V4'/%3E%3Crect x='7' y='14' width='10' height='6'/%3E%3C/svg%3E");}
.ic-download{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M12 3v12'/%3E%3Cpolyline points='7,10 12,15 17,10'/%3E%3Cpath d='M4 19h16'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M12 3v12'/%3E%3Cpolyline points='7,10 12,15 17,10'/%3E%3Cpath d='M4 19h16'/%3E%3C/svg%3E");}
.ic-trash{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpolyline points='4,7 20,7'/%3E%3Cpath d='M6 7l1 14a1 1 0 0 0 1 1h8a1 1 0 0 0 1-1l1-14'/%3E%3Cpath d='M9 7V4a1 1 0 0 1 1-1h4a1 1 0 0 1 1 1v3'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpolyline points='4,7 20,7'/%3E%3Cpath d='M6 7l1 14a1 1 0 0 0 1 1h8a1 1 0 0 0 1-1l1-14'/%3E%3Cpath d='M9 7V4a1 1 0 0 1 1-1h4a1 1 0 0 1 1 1v3'/%3E%3C/svg%3E");}
.ic-edit{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M3 21l4-1 12-12-3-3L4 17z'/%3E%3Cpath d='M14 5l3 3'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M3 21l4-1 12-12-3-3L4 17z'/%3E%3Cpath d='M14 5l3 3'/%3E%3C/svg%3E");}
.ic-alert{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M12 3l9.5 17H2.5L12 3z'/%3E%3Cline x1='12' y1='9.5' x2='12' y2='14'/%3E%3Cline x1='12' y1='17' x2='12' y2='17.2'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M12 3l9.5 17H2.5L12 3z'/%3E%3Cline x1='12' y1='9.5' x2='12' y2='14'/%3E%3Cline x1='12' y1='17' x2='12' y2='17.2'/%3E%3C/svg%3E");}
.ic-undo{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M4 9h10a5 5 0 0 1 0 10H9'/%3E%3Cpolyline points='8,4 4,9 8,14'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Cpath d='M4 9h10a5 5 0 0 1 0 10H9'/%3E%3Cpolyline points='8,4 4,9 8,14'/%3E%3C/svg%3E");}
.ic-clipboard{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Crect x='6' y='4' width='12' height='17' rx='1.5'/%3E%3Cpath d='M9 4V3a1 1 0 0 1 1-1h4a1 1 0 0 1 1 1v1'/%3E%3Cline x1='9' y1='10' x2='15' y2='10'/%3E%3Cline x1='9' y1='14' x2='15' y2='14'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Crect x='6' y='4' width='12' height='17' rx='1.5'/%3E%3Cpath d='M9 4V3a1 1 0 0 1 1-1h4a1 1 0 0 1 1 1v1'/%3E%3Cline x1='9' y1='10' x2='15' y2='10'/%3E%3Cline x1='9' y1='14' x2='15' y2='14'/%3E%3C/svg%3E");}
.ic-calendar{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Crect x='3' y='5' width='18' height='16' rx='1.5'/%3E%3Cline x1='3' y1='9' x2='21' y2='9'/%3E%3Cline x1='8' y1='3' x2='8' y2='7'/%3E%3Cline x1='16' y1='3' x2='16' y2='7'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Crect x='3' y='5' width='18' height='16' rx='1.5'/%3E%3Cline x1='3' y1='9' x2='21' y2='9'/%3E%3Cline x1='8' y1='3' x2='8' y2='7'/%3E%3Cline x1='16' y1='3' x2='16' y2='7'/%3E%3C/svg%3E");}
.ic-user{-webkit-mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Ccircle cx='12' cy='8' r='4'/%3E%3Cpath d='M4 20a8 8 0 0 1 16 0'/%3E%3C/svg%3E");mask-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='black' stroke-width='1.8'%3E%3Ccircle cx='12' cy='8' r='4'/%3E%3Cpath d='M4 20a8 8 0 0 1 16 0'/%3E%3C/svg%3E");}
</style>
</head>
<body>

<header>
  <div class="header-left">
    <div class="header-logo"><i class="ic ic-target ic-lg" style="background-color:#ffffff;"></i></div>
    <div>
      <div class="header-title">ระบบติดตามงาน & ให้คุณให้โทษ</div>
      <div class="header-sub">มอบหมายงาน · ติดตามสถานะ · คะแนนสะสม · ใบเตือน</div>
    </div>
  </div>
  <div class="header-right">
    <button class="header-badge no-print" id="btnInstallApp" style="display:none;border:none;cursor:pointer;">
      <i class="ic ic-download" style="color:#fff;"></i><span>ติดตั้งแอป</span>
    </button>
    <div class="header-badge" id="connectionBadge">
      <span class="badge-dot" id="connDot"></span>
      <span id="connText">เชื่อมต่อ...</span>
    </div>
  </div>
</header>

<div class="layout">
  <aside class="sidebar">
    <div class="sidebar-inner">
      <div class="nav-group">
        <div class="nav-group-label">ภาพรวม</div>
        <button class="nav-btn active" data-view="dashboard"><span class="icon"><i class="ic ic-grid"></i></span><span class="label">Dashboard</span></button>
      </div>
      <div class="nav-group">
        <div class="nav-group-label">งาน</div>
        <button class="nav-btn" data-view="board"><span class="icon"><i class="ic ic-clipboard"></i></span><span class="label">บอร์ดงาน</span></button>
        <button class="nav-btn" data-view="addtask"><span class="icon"><i class="ic ic-plus"></i></span><span class="label">มอบหมายงาน</span></button>
        <button class="nav-btn" data-view="overdue"><span class="icon"><i class="ic ic-clock"></i></span><span class="label">งานล่าช้า</span><span class="nbadge" id="overdueBadge" style="display:none;">0</span></button>
      </div>
      <div class="nav-group">
        <div class="nav-group-label">คุณ/โทษ</div>
        <button class="nav-btn" data-view="score"><span class="icon"><i class="ic ic-star"></i></span><span class="label">ให้คุณให้โทษ</span></button>
        <button class="nav-btn" data-view="leaderboard"><span class="icon"><i class="ic ic-trophy"></i></span><span class="label">กระดานคะแนน</span></button>
        <button class="nav-btn" data-view="scorelog"><span class="icon"><i class="ic ic-doc"></i></span><span class="label">ประวัติคะแนน</span></button>
      </div>
      <div class="nav-group">
        <div class="nav-group-label">ทีม</div>
        <button class="nav-btn" data-view="staff"><span class="icon"><i class="ic ic-users"></i></span><span class="label">จัดการพนักงาน</span></button>
      </div>
    </div>
    <div class="sidebar-footer">Firebase Realtime Sync</div>
  </aside>

  <main class="main">

    <!-- DASHBOARD -->
    <section id="view-dashboard" class="section active">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-grid ic-lg"></i> Dashboard</div>
        <div class="page-sub">ภาพรวมงานทั้งหมดและคะแนนทีม</div>
      </div>
      <div class="stats-grid">
        <div class="stat-card"><div class="stat-icon" style="background:#ececec;"><i class="ic ic-clipboard ic-lg" style="color:#2b2b2b;"></i></div><div><div class="stat-label">งานทั้งหมด</div><div class="stat-value" id="st_total">0</div></div></div>
        <div class="stat-card"><div class="stat-icon" style="background:#ececec;"><i class="ic ic-hourglass ic-lg" style="color:#6b6b6b;"></i></div><div><div class="stat-label">รอดำเนินการ</div><div class="stat-value" id="st_pending">0</div></div></div>
        <div class="stat-card"><div class="stat-icon" style="background:#e8f0fb;"><i class="ic ic-wrench ic-lg" style="color:#1d4ed8;"></i></div><div><div class="stat-label">กำลังทำ</div><div class="stat-value" id="st_progress">0</div></div></div>
        <div class="stat-card"><div class="stat-icon" style="background:#eafaf0;"><i class="ic ic-check ic-lg" style="color:#16a34a;"></i></div><div><div class="stat-label">เสร็จแล้ว</div><div class="stat-value" id="st_done">0</div></div></div>
        <div class="stat-card"><div class="stat-icon" style="background:#fdecec;"><i class="ic ic-clock ic-lg" style="color:#dc2626;"></i></div><div><div class="stat-label">ล่าช้า</div><div class="stat-value" id="st_late">0</div></div></div>
        <div class="stat-card"><div class="stat-icon" style="background:#fdf8e3;"><i class="ic ic-trophy ic-lg" style="color:#ca8a04;"></i></div><div><div class="stat-label">ผู้นำคะแนนเดือนนี้</div><div class="stat-value" id="st_top" style="font-size:16px;">-</div></div></div>
      </div>

      <div class="card" style="margin-bottom:14px;">
        <div class="card-title"><i class="ic ic-trophy"></i> อันดับคะแนนสูงสุด (Top 5)</div>
        <div id="topRanks"></div>
      </div>

      <div class="card">
        <div class="card-title">⏰ งานที่ใกล้ครบกำหนด / ล่าช้า</div>
        <div id="dueSoonList"></div>
      </div>
    </section>

    <!-- BOARD (Kanban) -->
    <section id="view-board" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-clipboard ic-lg"></i> บอร์ดงาน</div>
        <div class="page-sub">ลากดูสถานะงานทั้งหมด แยกตามขั้นตอน</div>
      </div>
      <div class="filter-row">
        <input id="boardSearch" placeholder="ค้นหางาน / ผู้รับผิดชอบ...">
        <select id="boardFilterDept"><option value="">ทุกแผนก</option></select>
        <select id="boardFilterPriority">
          <option value="">ทุกความสำคัญ</option>
          <option value="high">สูง</option>
          <option value="mid">กลาง</option>
          <option value="low">ต่ำ</option>
        </select>
      </div>
      <div class="kanban" id="kanbanWrap"></div>
    </section>

    <!-- ADD TASK -->
    <section id="view-addtask" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-plus ic-lg"></i> มอบหมายงานใหม่</div>
        <div class="page-sub">กรอกรายละเอียดงานและกำหนดผู้รับผิดชอบ</div>
      </div>
      <div class="card">
        <div class="form-grid">
          <div class="form-row" style="grid-column:1/-1;">
            <label>ชื่องาน <span style="color:var(--danger)">*</span></label>
            <input id="t_title" placeholder="เช่น ตรวจเช็คสภาพรถ ATV ก่อนใช้งาน">
          </div>
          <div class="form-row">
            <label>แผนก <span style="color:var(--danger)">*</span></label>
            <select id="t_dept"></select>
          </div>
          <div class="form-row">
            <label>ผู้รับผิดชอบ <span style="color:var(--danger)">*</span></label>
            <select id="t_assignee"></select>
          </div>
          <div class="form-row">
            <label>ความสำคัญ</label>
            <select id="t_priority">
              <option value="mid">กลาง</option>
              <option value="high">สูง</option>
              <option value="low">ต่ำ</option>
            </select>
          </div>
          <div class="form-row">
            <label>กำหนดเสร็จ <span style="color:var(--danger)">*</span></label>
            <input id="t_due" type="date">
          </div>
          <div class="form-row" style="grid-column:1/-1;">
            <label>รายละเอียดงาน</label>
            <textarea id="t_desc" placeholder="อธิบายรายละเอียด ขั้นตอน หรือเงื่อนไขของงาน"></textarea>
          </div>
        </div>
        <div style="margin-top:14px;display:flex;gap:8px;">
          <button class="btn-primary" id="btnSaveTask"><i class="ic ic-save" style="color:#fff;"></i> มอบหมายงาน</button>
          <button class="btn-ghost" id="btnClearTask"><i class="ic ic-x"></i> ล้างข้อมูล</button>
        </div>
      </div>
    </section>

    <!-- OVERDUE -->
    <section id="view-overdue" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-clock ic-lg"></i> งานล่าช้า</div>
        <div class="page-sub">งานที่เกินกำหนดและยังไม่เสร็จ — พิจารณาตัดคะแนน</div>
      </div>
      <div id="overdueList"></div>
      <div id="overdueEmpty" class="empty-state" style="display:none;">
        <div class="empty-icon"><i class="ic ic-check ic-lg" style="width:1.6em;height:1.6em;color:#16a34a;"></i></div><div class="empty-msg">ไม่มีงานล่าช้า เยี่ยมมาก!</div>
      </div>
    </section>

    <!-- SCORE GIVE/TAKE -->
    <section id="view-score" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-star ic-lg"></i> ให้คุณให้โทษ</div>
        <div class="page-sub">บันทึกการให้คะแนน หรือตัดคะแนนพนักงาน พร้อมเหตุผล</div>
      </div>
      <div class="card">
        <div class="score-toggle" id="scoreToggle">
          <button class="stog-active give" data-mode="give" id="btnModeGive"><i class="ic ic-check" style="color:#fff;"></i> ให้คุณ (เพิ่มคะแนน)</button>
          <button class="stog-inactive" data-mode="take" id="btnModeTake"><i class="ic ic-x"></i> ให้โทษ (ตัดคะแนน)</button>
        </div>
        <div class="form-grid">
          <div class="form-row">
            <label>พนักงาน <span style="color:var(--danger)">*</span></label>
            <select id="s_staff"></select>
          </div>
          <div class="form-row">
            <label>คะแนน <span style="color:var(--danger)">*</span></label>
            <select id="s_points"></select>
          </div>
          <div class="form-row" style="grid-column:1/-1;">
            <label>เหตุผล <span style="color:var(--danger)">*</span></label>
            <textarea id="s_reason" placeholder="ระบุเหตุผล เช่น ทำงานเสร็จก่อนกำหนด, มาสาย, ลูกค้าชมเชย, ทำของเสียหาย ฯลฯ"></textarea>
          </div>
        </div>
        <div style="margin-top:14px;">
          <button class="btn-success" id="btnSubmitScore"><i class="ic ic-save" style="color:#fff;"></i> บันทึก</button>
        </div>
      </div>
    </section>

    <!-- LEADERBOARD -->
    <section id="view-leaderboard" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-trophy ic-lg"></i> กระดานคะแนน</div>
        <div class="page-sub">จัดอันดับพนักงานตามคะแนนสะสม</div>
      </div>
      <div class="filter-row">
        <select id="lbDeptFilter"><option value="">ทุกแผนก</option></select>
        <select id="lbPeriod">
          <option value="all">ทั้งหมด</option>
          <option value="month">เดือนนี้</option>
          <option value="year">ปีนี้</option>
        </select>
      </div>
      <div class="card">
        <div id="leaderboardList"></div>
      </div>
    </section>

    <!-- SCORE LOG -->
    <section id="view-scorelog" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-doc ic-lg"></i> ประวัติการให้คะแนน</div>
        <div class="page-sub">บันทึกการให้คุณ/ให้โทษทั้งหมด พร้อมยกเลิกรายการได้</div>
      </div>
      <div class="filter-row">
        <input id="logSearch" placeholder="ค้นหาชื่อ / เหตุผล...">
        <select id="logTypeFilter">
          <option value="">ทั้งหมด</option>
          <option value="give">ให้คุณ</option>
          <option value="take">ให้โทษ</option>
        </select>
      </div>
      <div id="scoreLogList"></div>
      <div id="scoreLogEmpty" class="empty-state" style="display:none;">
        <div class="empty-icon"><i class="ic ic-doc ic-lg" style="width:1.6em;height:1.6em;color:#9a9a9a;"></i></div><div class="empty-msg">ยังไม่มีประวัติ</div>
      </div>
    </section>

    <!-- STAFF -->
    <section id="view-staff" class="section">
      <div class="page-header">
        <div class="page-title"><i class="ic ic-users ic-lg"></i> จัดการพนักงาน</div>
        <div class="page-sub">เพิ่ม/แก้ไขรายชื่อพนักงานและแผนก</div>
      </div>
      <div class="card" style="margin-bottom:14px;">
        <div class="card-title"><i class="ic ic-plus"></i> เพิ่มพนักงานใหม่</div>
        <div class="form-grid">
          <div class="form-row">
            <label>ชื่อพนักงาน <span style="color:var(--danger)">*</span></label>
            <input id="st_name" placeholder="ชื่อ-นามสกุล หรือชื่อเล่น">
          </div>
          <div class="form-row">
            <label>แผนก <span style="color:var(--danger)">*</span></label>
            <input id="st_dept" list="deptList" placeholder="เช่น ATV, ออฟฟิศ, ครัว, สวน">
            <datalist id="deptList"></datalist>
          </div>
          <div class="form-row">
            <label>ตำแหน่ง</label>
            <input id="st_role" placeholder="เช่น ไกด์, ช่าง, พนักงานต้อนรับ">
          </div>
        </div>
        <div style="margin-top:14px;"><button class="btn-primary" id="btnAddStaff"><i class="ic ic-save" style="color:#fff;"></i> เพิ่มพนักงาน</button></div>
      </div>
      <div class="card" style="padding:0;overflow:hidden;">
        <div class="table-wrap">
          <table>
            <thead><tr><th>ชื่อ</th><th>แผนก</th><th>ตำแหน่ง</th><th class="text-right">คะแนนสะสม</th><th class="text-center">การกระทำ</th></tr></thead>
            <tbody id="staffBody"></tbody>
          </table>
        </div>
      </div>
    </section>

  </main>
</div>

<div id="toast-container"></div>

<div id="confirmOverlay" class="confirm-overlay">
  <div class="confirm-box">
    <div class="confirm-title" id="confirmTitle">ยืนยัน</div>
    <div class="confirm-msg" id="confirmMsg"></div>
    <div class="confirm-footer">
      <button class="btn-ghost" id="confirmNo">ยกเลิก</button>
      <button class="btn-danger" id="confirmYes">ยืนยัน</button>
    </div>
  </div>
</div>

<!-- TASK DETAIL POPUP -->
<div id="popupTask" class="popup-overlay">
  <div class="popup-card">
    <div class="popup-title"><i class="ic ic-clipboard"></i> รายละเอียดงาน</div>
    <div class="form-grid">
      <div class="form-row" style="grid-column:1/-1;">
        <label>ชื่องาน</label>
        <input id="d_title">
      </div>
      <div class="form-row">
        <label>แผนก</label>
        <select id="d_dept"></select>
      </div>
      <div class="form-row">
        <label>ผู้รับผิดชอบ</label>
        <select id="d_assignee"></select>
      </div>
      <div class="form-row">
        <label>ความสำคัญ</label>
        <select id="d_priority"><option value="mid">กลาง</option><option value="high">สูง</option><option value="low">ต่ำ</option></select>
      </div>
      <div class="form-row">
        <label>กำหนดเสร็จ</label>
        <input id="d_due" type="date">
      </div>
      <div class="form-row" style="grid-column:1/-1;">
        <label>สถานะ</label>
        <select id="d_status">
          <option value="pending">รอดำเนินการ</option>
          <option value="progress">กำลังทำ</option>
          <option value="done">เสร็จแล้ว</option>
        </select>
      </div>
      <div class="form-row" style="grid-column:1/-1;">
        <label>รายละเอียด</label>
        <textarea id="d_desc"></textarea>
      </div>
    </div>
    <input type="hidden" id="d_id">
    <div class="popup-footer" style="justify-content:space-between;">
      <button class="btn-ghost" id="btnDeleteTask" style="color:var(--danger);border-color:var(--danger);"><i class="ic ic-trash" style="color:var(--danger);"></i> ลบงาน</button>
      <div style="display:flex;gap:8px;">
        <button class="btn-ghost" id="btnCloseTask">ปิด</button>
        <button class="btn-primary" id="btnSaveTaskDetail"><i class="ic ic-save" style="color:#fff;"></i> บันทึก</button>
      </div>
    </div>
  </div>
</div>

<!-- EDIT STAFF POPUP -->
<div id="popupStaff" class="popup-overlay">
  <div class="popup-card">
    <div class="popup-title"><i class="ic ic-edit"></i> แก้ไขพนักงาน</div>
    <div class="form-grid">
      <div class="form-row"><label>ชื่อ</label><input id="es_name"></div>
      <div class="form-row"><label>แผนก</label><input id="es_dept"></div>
      <div class="form-row" style="grid-column:1/-1;"><label>ตำแหน่ง</label><input id="es_role"></div>
    </div>
    <input type="hidden" id="es_id">
    <div class="popup-footer">
      <button class="btn-ghost" id="btnCloseStaffEdit">ปิด</button>
      <button class="btn-primary" id="btnSaveStaffEdit"><i class="ic ic-save" style="color:#fff;"></i> บันทึก</button>
    </div>
  </div>
</div>

<script src="https://www.gstatic.com/firebasejs/9.23.0/firebase-app-compat.js"></script>
<script src="https://www.gstatic.com/firebasejs/9.23.0/firebase-firestore-compat.js"></script>
<script>
/* ════════════════ FIREBASE ════════════════ */
const fbConfig = {
  apiKey:"AIzaSyBo8aIL2e1XLdS4BeOPEreXaA3IyWDTiHY",
  authDomain:"stock-69302.firebaseapp.com",
  projectId:"stock-69302",
  storageBucket:"stock-69302.firebasestorage.app",
  messagingSenderId:"301831402512",
  appId:"1:301831402512:web:290a578b80c199314bc695"
};
if(!firebase.apps.length) firebase.initializeApp(fbConfig);
const db = firebase.firestore();
// แยก collections ใหม่ ไม่ชนกับระบบสต็อกเดิม: tasks, staff, scorelog

/* ════════════════ STATE ════════════════ */
let tasks=[];
let staff=[];
let scoreLog=[];
let scoreMode='give';

/* ════════════════ UTILS ════════════════ */
function todayStr(){ return new Date().toISOString().slice(0,10); }
function esc(s){ return String(s||'').replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;'); }
const MONTHS_TH=['ม.ค.','ก.พ.','มี.ค.','เม.ย.','พ.ค.','มิ.ย.','ก.ค.','ส.ค.','ก.ย.','ต.ค.','พ.ย.','ธ.ค.'];
function thaiDate(ds){
  if(!ds) return '-';
  const p=String(ds).split('-');
  let d;
  if(p.length===3) d=new Date(+p[0],+p[1]-1,+p[2]);
  else d=new Date(ds);
  if(isNaN(d.getTime())) return ds;
  return d.getDate()+' '+MONTHS_TH[d.getMonth()]+' '+(d.getFullYear()+543);
}
function thaiDateTime(val){
  let d;
  if(val && typeof val.toDate==='function') d=val.toDate();
  else if(val) d=new Date(val);
  else return '-';
  if(isNaN(d.getTime())) return String(val);
  const h=String(d.getHours()).padStart(2,'0');
  const m=String(d.getMinutes()).padStart(2,'0');
  return d.getDate()+' '+MONTHS_TH[d.getMonth()]+' '+(d.getFullYear()+543)+' '+h+':'+m+' น.';
}
function fmtInt(n){ return Number(n||0).toLocaleString('th-TH'); }
function daysUntil(dateStr){
  if(!dateStr) return null;
  const d=new Date(dateStr+'T00:00:00');
  const t=new Date(); t.setHours(0,0,0,0);
  return Math.round((d-t)/86400000);
}
function initials(name){
  if(!name) return '?';
  const parts=name.trim().split(/\s+/);
  return parts.length>1 ? (parts[0][0]+parts[1][0]).toUpperCase() : name.slice(0,2).toUpperCase();
}

/* ════════════════ TOAST ════════════════ */
function toast(msg, type='', dur=3200){
  const c=document.getElementById('toast-container');
  const t=document.createElement('div');
  t.className='toast'+(type?' '+type:'');
  t.innerHTML=`<span style="flex:1">${msg}</span><span class="t-close" onclick="this.parentNode.remove()">✕</span>`;
  c.appendChild(t);
  setTimeout(()=>{ t.style.transition='opacity .3s'; t.style.opacity='0'; setTimeout(()=>t.remove(),320); }, dur);
}

/* ════════════════ CONFIRM ════════════════ */
function showConfirm(title, msg, okLabel, okClass, onOk){
  const ov=document.getElementById('confirmOverlay');
  document.getElementById('confirmTitle').textContent=title;
  document.getElementById('confirmMsg').textContent=msg;
  const yes=document.getElementById('confirmYes');
  yes.textContent=okLabel||'ยืนยัน';
  yes.className='btn-sm '+(okClass||'btn-danger');
  ov.style.display='flex';
  const clone=yes.cloneNode(true);
  yes.parentNode.replaceChild(clone,yes);
  clone.addEventListener('click',()=>{ ov.style.display='none'; onOk(); });
  document.getElementById('confirmNo').onclick=()=>{ ov.style.display='none'; };
  ov.onclick=(e)=>{ if(e.target===ov) ov.style.display='none'; };
}

/* ════════════════ NAV ════════════════ */
function setupNav(){
  document.querySelectorAll('.nav-btn[data-view]').forEach(btn=>{
    btn.addEventListener('click',()=>{
      document.querySelectorAll('.nav-btn').forEach(b=>b.classList.remove('active'));
      btn.classList.add('active');
      document.querySelectorAll('.section').forEach(s=>s.classList.remove('active'));
      document.getElementById('view-'+btn.dataset.view).classList.add('active');
      const v=btn.dataset.view;
      if(v==='dashboard') renderDashboard();
      if(v==='board') renderBoard();
      if(v==='addtask') fillTaskFormSelectors();
      if(v==='overdue') renderOverdue();
      if(v==='score') fillScoreSelectors();
      if(v==='leaderboard') renderLeaderboard();
      if(v==='scorelog') renderScoreLog();
      if(v==='staff') renderStaffTable();
    });
  });
}

/* ════════════════ DEPT LIST DERIVED FROM STAFF ════════════════ */
function getDepts(){
  return [...new Set(staff.map(s=>s.dept).filter(Boolean))].sort();
}
function fillDeptSelectors(){
  const depts=getDepts();
  ['t_dept','d_dept','boardFilterDept','lbDeptFilter'].forEach(id=>{
    const sel=document.getElementById(id);
    if(!sel) return;
    const keepFirst = id==='boardFilterDept'||id==='lbDeptFilter';
    const cur=sel.value;
    sel.innerHTML = keepFirst ? '<option value="">ทุกแผนก</option>' : '';
    depts.forEach(d=>{ const o=document.createElement('option'); o.value=d; o.textContent=d; sel.appendChild(o); });
    if(depts.includes(cur)) sel.value=cur;
  });
  const dl=document.getElementById('deptList');
  if(dl){ dl.innerHTML=''; depts.forEach(d=>{ const o=document.createElement('option'); o.value=d; dl.appendChild(o); }); }
}
function fillStaffSelectors(){
  ['t_assignee','d_assignee','s_staff'].forEach(id=>{
    const sel=document.getElementById(id);
    if(!sel) return;
    const cur=sel.value;
    sel.innerHTML='';
    if(!staff.length){ sel.innerHTML='<option value="">— ยังไม่มีพนักงาน —</option>'; return; }
    staff.forEach(s=>{ const o=document.createElement('option'); o.value=s.id; o.textContent=s.name+(s.dept?' ('+s.dept+')':''); sel.appendChild(o); });
    if(staff.find(s=>s.id===cur)) sel.value=cur;
  });
}
function fillTaskFormSelectors(){ fillDeptSelectors(); fillStaffSelectors(); document.getElementById('t_due').value=document.getElementById('t_due').value||todayStr(); }
function fillScoreSelectors(){
  fillStaffSelectors();
  const sel=document.getElementById('s_points');
  sel.innerHTML='';
  const giveOpts=[1,2,3,5,10];
  const takeOpts=[1,2,3,5,10];
  (scoreMode==='give'?giveOpts:takeOpts).forEach(p=>{
    const o=document.createElement('option'); o.value=p; o.textContent=p+' คะแนน'; sel.appendChild(o);
  });
}

/* ════════════════ TASK STATUS HELPERS ════════════════ */
function taskEffectiveStatus(t){
  if(t.status==='done') return 'done';
  const d=daysUntil(t.due);
  if(d!==null && d<0) return 'late';
  return t.status||'pending';
}
function staffName(id){ const s=staff.find(x=>x.id===id); return s?s.name:'(ไม่พบ)'; }
function priorityTag(p){
  if(p==='high') return '<span class="tag tag-high">สูง</span>';
  if(p==='low') return '<span class="tag tag-low">ต่ำ</span>';
  return '<span class="tag tag-mid">กลาง</span>';
}
function statusTag(s){
  if(s==='done') return '<span class="tag tag-done">เสร็จแล้ว</span>';
  if(s==='progress') return '<span class="tag tag-progress">กำลังทำ</span>';
  if(s==='late') return '<span class="tag tag-late">ล่าช้า</span>';
  return '<span class="tag tag-pending">รอดำเนินการ</span>';
}

/* ════════════════ DASHBOARD ════════════════ */
function renderDashboard(){
  const statuses=tasks.map(taskEffectiveStatus);
  document.getElementById('st_total').textContent=fmtInt(tasks.length);
  document.getElementById('st_pending').textContent=fmtInt(statuses.filter(s=>s==='pending').length);
  document.getElementById('st_progress').textContent=fmtInt(statuses.filter(s=>s==='progress').length);
  document.getElementById('st_done').textContent=fmtInt(statuses.filter(s=>s==='done').length);
  const lateCount=statuses.filter(s=>s==='late').length;
  document.getElementById('st_late').textContent=fmtInt(lateCount);

  const ob=document.getElementById('overdueBadge');
  ob.textContent=lateCount; ob.style.display=lateCount?'inline':'none';

  // top scorer this month
  const thisM=todayStr().slice(0,7);
  const monthScores={};
  scoreLog.filter(l=>(l.date||'').slice(0,7)===thisM).forEach(l=>{
    monthScores[l.staffId]=(monthScores[l.staffId]||0)+(l.type==='take'?-l.points:l.points);
  });
  const topId=Object.keys(monthScores).sort((a,b)=>monthScores[b]-monthScores[a])[0];
  document.getElementById('st_top').textContent = topId ? `${staffName(topId)} (${monthScores[topId]>0?'+':''}${monthScores[topId]})` : '-';

  // top 5 ranks (all time)
  const totals=computeTotals();
  const sorted=Object.entries(totals).sort((a,b)=>b[1]-a[1]).slice(0,5);
  const container=document.getElementById('topRanks');
  if(!sorted.length){ container.innerHTML='<div class="empty-state" style="padding:16px;"><div class="empty-msg">ยังไม่มีข้อมูลคะแนน</div></div>'; }
  else {
    container.innerHTML=sorted.map(([id,score],i)=>{
      const rankClass=i===0?'gold':i===1?'silver':i===2?'bronze':'';
      const s=staff.find(x=>x.id===id);
      return `<div class="rank-card">
        <div class="rank-num ${rankClass}">${i+1}</div>
        <div class="rank-avatar">${initials(s?s.name:'?')}</div>
        <div class="rank-info"><div class="rank-name">${esc(s?s.name:'(ไม่พบ)')}</div><div class="rank-meta">${esc(s?s.dept:'')}</div></div>
        <div class="rank-score ${score>=0?'pos':'neg'}">${score>0?'+':''}${score}</div>
      </div>`;
    }).join('');
  }

  // due soon / late
  const upcoming=tasks.filter(t=>taskEffectiveStatus(t)!=='done').map(t=>({...t, _days:daysUntil(t.due)})).sort((a,b)=>a._days-b._days).slice(0,8);
  const dueDiv=document.getElementById('dueSoonList');
  if(!upcoming.length){ dueDiv.innerHTML='<div class="empty-state" style="padding:16px;"><div class="empty-msg">ไม่มีงานที่ต้องติดตาม</div></div>'; }
  else {
    dueDiv.innerHTML=upcoming.map(t=>{
      const d=t._days;
      const dLabel = d<0 ? `เกินกำหนด ${Math.abs(d)} วัน` : d===0 ? 'ครบกำหนดวันนี้' : `เหลือ ${d} วัน`;
      const color = d<0 ? 'var(--danger)' : d<=2 ? 'var(--warning)' : 'var(--text2)';
      return `<div class="log-card">
        <div class="log-info">
          <div class="log-name">${esc(t.title)}</div>
          <div class="log-reason">${esc(staffName(t.assignee))} · ${esc(t.dept||'')}</div>
        </div>
        <div style="text-align:right;">
          ${statusTag(taskEffectiveStatus(t))}
          <div style="font-size:11px;color:${color};margin-top:4px;font-weight:600;">${dLabel}</div>
        </div>
      </div>`;
    }).join('');
  }
}

function computeTotals(){
  const totals={};
  staff.forEach(s=>totals[s.id]=0);
  scoreLog.forEach(l=>{
    totals[l.staffId]=(totals[l.staffId]||0)+(l.type==='take'?-l.points:l.points);
  });
  return totals;
}

/* ════════════════ BOARD (KANBAN) ════════════════ */
function renderBoard(){
  fillDeptSelectors();
  const kw=(document.getElementById('boardSearch').value||'').toLowerCase();
  const deptF=document.getElementById('boardFilterDept').value;
  const prioF=document.getElementById('boardFilterPriority').value;
  let filtered=tasks.filter(t=>{
    if(kw && !((t.title||'').toLowerCase().includes(kw) || staffName(t.assignee).toLowerCase().includes(kw))) return false;
    if(deptF && t.dept!==deptF) return false;
    if(prioF && t.priority!==prioF) return false;
    return true;
  });
  const cols={pending:[],progress:[],late:[],done:[]};
  filtered.forEach(t=>cols[taskEffectiveStatus(t)].push(t));
  const colMeta=[
    {key:'pending',label:'<i class="ic ic-hourglass" style="color:#6b6b6b;"></i> รอดำเนินการ'},
    {key:'progress',label:'<i class="ic ic-wrench" style="color:#1d4ed8;"></i> กำลังทำ'},
    {key:'late',label:'<i class="ic ic-clock" style="color:#dc2626;"></i> ล่าช้า'},
    {key:'done',label:'<i class="ic ic-check" style="color:#16a34a;"></i> เสร็จแล้ว'}
  ];
  document.getElementById('kanbanWrap').innerHTML=colMeta.map(c=>{
    const list=cols[c.key].sort((a,b)=>(a.due||'').localeCompare(b.due||''));
    return `<div class="kanban-col">
      <div class="kanban-col-title"><span>${c.label}</span><span class="kanban-col-count">${list.length}</span></div>
      ${list.map(t=>{
        const d=daysUntil(t.due);
        const cls = d!==null && d<0 && t.status!=='done' ? 'overdue' : (d!==null && d<=2 && t.status!=='done' ? 'due-soon' : '');
        return `<div class="task-card ${cls}" data-id="${t.id}">
          <div class="task-card-title">${esc(t.title)}</div>
          <div class="task-card-meta">
            ${priorityTag(t.priority)}
            <span class="task-card-avatar"><i class="ic ic-user" style="width:0.85em;height:0.85em;"></i> ${esc(staffName(t.assignee))}</span>
          </div>
          <div class="task-card-meta"><span><i class="ic ic-calendar" style="width:0.85em;height:0.85em;"></i> ${thaiDate(t.due)}</span><span>· ${esc(t.dept||'')}</span></div>
        </div>`;
      }).join('') || '<div style="font-size:12px;color:var(--text2);text-align:center;padding:14px 0;">ไม่มีงาน</div>'}
    </div>`;
  }).join('');
  document.querySelectorAll('.task-card').forEach(card=>{
    card.addEventListener('click',()=>openTaskDetail(card.dataset.id));
  });
}

/* ════════════════ OVERDUE ════════════════ */
function renderOverdue(){
  const late=tasks.filter(t=>taskEffectiveStatus(t)==='late').sort((a,b)=>(a.due||'').localeCompare(b.due||''));
  document.getElementById('overdueEmpty').style.display=late.length?'none':'block';
  document.getElementById('overdueList').innerHTML=late.map(t=>{
    const d=daysUntil(t.due);
    return `<div class="log-card">
      <div class="log-info">
        <div class="log-name">${esc(t.title)}</div>
        <div class="log-reason">ผู้รับผิดชอบ: <b>${esc(staffName(t.assignee))}</b> · แผนก: ${esc(t.dept||'-')} · กำหนด: ${thaiDate(t.due)}</div>
        <div class="log-meta">เกินกำหนดมาแล้ว ${Math.abs(d)} วัน</div>
      </div>
      <div style="display:flex;flex-direction:column;gap:6px;align-items:flex-end;">
        ${priorityTag(t.priority)}
        <button class="btn-danger btn-xs btn-penalize" data-id="${t.assignee}" data-title="${esc(t.title)}"><i class="ic ic-alert" style="color:#fff;width:0.85em;height:0.85em;"></i> ตัดคะแนน</button>
      </div>
    </div>`;
  }).join('');
  document.querySelectorAll('.btn-penalize').forEach(btn=>{
    btn.addEventListener('click',()=>{
      scoreMode='take';
      document.querySelectorAll('.nav-btn').forEach(b=>b.classList.remove('active'));
      document.querySelector('.nav-btn[data-view="score"]').classList.add('active');
      document.querySelectorAll('.section').forEach(s=>s.classList.remove('active'));
      document.getElementById('view-score').classList.add('active');
      switchScoreMode('take');
      fillScoreSelectors();
      document.getElementById('s_staff').value=btn.dataset.id;
      document.getElementById('s_reason').value='งานล่าช้า: '+btn.dataset.title;
    });
  });
}

/* ════════════════ TASK CRUD ════════════════ */
function saveTask(){
  const title=document.getElementById('t_title').value.trim();
  const dept=document.getElementById('t_dept').value;
  const assignee=document.getElementById('t_assignee').value;
  const priority=document.getElementById('t_priority').value;
  const due=document.getElementById('t_due').value;
  const desc=document.getElementById('t_desc').value.trim();
  if(!title||!dept||!assignee||!due){ toast('กรุณากรอกข้อมูลให้ครบ (ชื่องาน, แผนก, ผู้รับผิดชอบ, กำหนดเสร็จ)','error'); return; }
  db.collection('tasks').add({
    title, dept, assignee, priority, due, desc,
    status:'pending', created:new Date().toISOString(),
    created_ts:firebase.firestore.FieldValue.serverTimestamp()
  }).then(()=>{
    toast(`มอบหมายงาน '${title}' ให้ ${staffName(assignee)} เรียบร้อย ✔`,'success');
    ['t_title','t_desc'].forEach(id=>document.getElementById(id).value='');
  });
}
function openTaskDetail(id){
  const t=tasks.find(x=>x.id===id); if(!t) return;
  fillDeptSelectors(); fillStaffSelectors();
  document.getElementById('d_id').value=t.id;
  document.getElementById('d_title').value=t.title;
  document.getElementById('d_dept').value=t.dept;
  document.getElementById('d_assignee').value=t.assignee;
  document.getElementById('d_priority').value=t.priority||'mid';
  document.getElementById('d_due').value=t.due;
  document.getElementById('d_status').value=t.status||'pending';
  document.getElementById('d_desc').value=t.desc||'';
  document.getElementById('popupTask').style.display='flex';
}
function saveTaskDetail(){
  const id=document.getElementById('d_id').value;
  const wasStatus=tasks.find(x=>x.id===id)?.status;
  const newStatus=document.getElementById('d_status').value;
  const updates={
    title:document.getElementById('d_title').value.trim(),
    dept:document.getElementById('d_dept').value,
    assignee:document.getElementById('d_assignee').value,
    priority:document.getElementById('d_priority').value,
    due:document.getElementById('d_due').value,
    status:newStatus,
    desc:document.getElementById('d_desc').value.trim()
  };
  if(newStatus==='done' && wasStatus!=='done') updates.completed_at=new Date().toISOString();
  db.collection('tasks').doc(id).update(updates).then(()=>{
    document.getElementById('popupTask').style.display='none';
    toast('บันทึกงานเรียบร้อย ✔','success');
    if(newStatus==='done' && wasStatus!=='done'){
      const t=tasks.find(x=>x.id===id);
      const onTime = t && daysUntil(t.due)>=0;
      toast(onTime ? 'งานเสร็จตรงเวลา — พิจารณาให้คะแนนเพิ่ม ✅' : 'งานเสร็จล่าช้ากว่ากำหนด','warn',4500);
    }
  });
}
function deleteTask(){
  const id=document.getElementById('d_id').value;
  const t=tasks.find(x=>x.id===id); if(!t) return;
  showConfirm('ลบงาน',`ลบงาน '${t.title}' ออกจากระบบ? ไม่สามารถกู้คืนได้`,'ลบ','btn-danger btn-sm',()=>{
    db.collection('tasks').doc(id).delete().then(()=>{
      document.getElementById('popupTask').style.display='none';
      toast('ลบงานเรียบร้อย','warn');
    });
  });
}

/* ════════════════ SCORE GIVE/TAKE ════════════════ */
function switchScoreMode(mode){
  scoreMode=mode;
  const giveBtn=document.getElementById('btnModeGive');
  const takeBtn=document.getElementById('btnModeTake');
  if(mode==='give'){
    giveBtn.className='stog-active give'; takeBtn.className='stog-inactive';
  } else {
    takeBtn.className='stog-active take'; giveBtn.className='stog-inactive';
  }
  fillScoreSelectors();
}
function submitScore(){
  const staffId=document.getElementById('s_staff').value;
  const points=+document.getElementById('s_points').value||0;
  const reason=document.getElementById('s_reason').value.trim();
  if(!staffId||!reason){ toast('กรุณาเลือกพนักงานและระบุเหตุผล','error'); return; }
  if(points<=0){ toast('กรุณาเลือกคะแนน','error'); return; }
  db.collection('scorelog').add({
    staffId, points, type:scoreMode, reason,
    date:todayStr(), time:new Date().toISOString(),
    time_ts:firebase.firestore.FieldValue.serverTimestamp()
  }).then(()=>{
    const label=scoreMode==='give'?'ให้คุณ':'ให้โทษ';
    toast(`บันทึก${label} ${staffName(staffId)} ${points} คะแนนเรียบร้อย ✔`, scoreMode==='give'?'success':'warn');
    document.getElementById('s_reason').value='';
  });
}

/* ════════════════ LEADERBOARD ════════════════ */
function renderLeaderboard(){
  fillDeptSelectors();
  const deptF=document.getElementById('lbDeptFilter').value;
  const period=document.getElementById('lbPeriod').value;
  const today=todayStr();
  let logs=scoreLog;
  if(period==='month') logs=logs.filter(l=>(l.date||'').slice(0,7)===today.slice(0,7));
  if(period==='year') logs=logs.filter(l=>(l.date||'').slice(0,4)===today.slice(0,4));
  const totals={};
  staff.forEach(s=>{ if(!deptF||s.dept===deptF) totals[s.id]=0; });
  logs.forEach(l=>{ if(totals[l.staffId]!==undefined) totals[l.staffId]+=(l.type==='take'?-l.points:l.points); });
  const sorted=Object.entries(totals).sort((a,b)=>b[1]-a[1]);
  const div=document.getElementById('leaderboardList');
  if(!sorted.length){ div.innerHTML='<div class="empty-state"><div class="empty-icon"><i class="ic ic-trophy ic-lg" style="width:1.6em;height:1.6em;color:#9a9a9a;"></i></div><div class="empty-msg">ยังไม่มีข้อมูล</div></div>'; return; }
  div.innerHTML=sorted.map(([id,score],i)=>{
    const rankClass=i===0?'gold':i===1?'silver':i===2?'bronze':'';
    const s=staff.find(x=>x.id===id);
    const giveCount=logs.filter(l=>l.staffId===id&&l.type==='give').length;
    const takeCount=logs.filter(l=>l.staffId===id&&l.type==='take').length;
    return `<div class="rank-card">
      <div class="rank-num ${rankClass}">${i+1}</div>
      <div class="rank-avatar">${initials(s?s.name:'?')}</div>
      <div class="rank-info">
        <div class="rank-name">${esc(s?s.name:'(ไม่พบ)')}</div>
        <div class="rank-meta">${esc(s?s.dept:'')} · ✅ ${giveCount} ครั้ง · ❌ ${takeCount} ครั้ง</div>
      </div>
      <div class="rank-score ${score>=0?'pos':'neg'}">${score>0?'+':''}${score}</div>
    </div>`;
  }).join('');
}

/* ════════════════ SCORE LOG ════════════════ */
function renderScoreLog(){
  const kw=(document.getElementById('logSearch').value||'').toLowerCase();
  const typeF=document.getElementById('logTypeFilter').value;
  let filtered=scoreLog.slice().sort((a,b)=>((b.date||'')+(b.time||'')).localeCompare((a.date||'')+(a.time||'')));
  if(kw) filtered=filtered.filter(l=>staffName(l.staffId).toLowerCase().includes(kw)||(l.reason||'').toLowerCase().includes(kw));
  if(typeF) filtered=filtered.filter(l=>l.type===typeF);
  document.getElementById('scoreLogEmpty').style.display=filtered.length?'none':'block';
  document.getElementById('scoreLogList').innerHTML=filtered.map(l=>{
    const sign=l.type==='take'?'-':'+';
    return `<div class="log-card">
      <div class="log-info">
        <div class="log-name">${esc(staffName(l.staffId))} ${l.type==='give'?'✅':'❌'}</div>
        <div class="log-reason">${esc(l.reason)}</div>
        <div class="log-meta">${thaiDate(l.date)} · บันทึกเมื่อ ${thaiDateTime(l.time_ts||l.time)}</div>
      </div>
      <div style="display:flex;flex-direction:column;align-items:flex-end;gap:6px;">
        <div class="log-points ${l.type==='take'?'neg':'pos'}">${sign}${l.points}</div>
        <button class="btn-ghost btn-xs btn-undo-score" data-id="${l.id}" style="color:var(--text2);">↩ ยกเลิก</button>
      </div>
    </div>`;
  }).join('');
  document.querySelectorAll('.btn-undo-score').forEach(btn=>{
    btn.addEventListener('click',()=>{
      showConfirm('ยกเลิกรายการคะแนน','ยืนยันลบรายการนี้ออกจากประวัติ?','ลบ','btn-danger btn-sm',()=>{
        db.collection('scorelog').doc(btn.dataset.id).delete().then(()=>toast('ยกเลิกรายการเรียบร้อย','warn'));
      });
    });
  });
}

/* ════════════════ STAFF CRUD ════════════════ */
function addStaff(){
  const name=document.getElementById('st_name').value.trim();
  const dept=document.getElementById('st_dept').value.trim();
  const role=document.getElementById('st_role').value.trim();
  if(!name||!dept){ toast('กรุณากรอกชื่อและแผนก','error'); return; }
  db.collection('staff').add({ name, dept, role, created:new Date().toISOString() }).then(()=>{
    toast(`เพิ่มพนักงาน '${name}' เรียบร้อย ✔`,'success');
    ['st_name','st_dept','st_role'].forEach(id=>document.getElementById(id).value='');
  });
}
function renderStaffTable(){
  const totals=computeTotals();
  document.getElementById('staffBody').innerHTML=staff.map(s=>{
    const score=totals[s.id]||0;
    return `<tr>
      <td><strong>${esc(s.name)}</strong></td>
      <td>${esc(s.dept||'-')}</td>
      <td class="text-muted">${esc(s.role||'-')}</td>
      <td class="text-right"><span style="font-weight:700;color:${score>=0?'var(--success)':'var(--danger)'}">${score>0?'+':''}${score}</span></td>
      <td class="text-center">
        <button class="btn-primary btn-xs btn-edit-staff" data-id="${s.id}">แก้ไข</button>
        <button class="btn-ghost btn-xs btn-del-staff" data-id="${s.id}" style="color:var(--danger);border-color:var(--danger);">ลบ</button>
      </td>
    </tr>`;
  }).join('');
  document.querySelectorAll('.btn-edit-staff').forEach(b=>b.addEventListener('click',()=>openStaffEdit(b.dataset.id)));
  document.querySelectorAll('.btn-del-staff').forEach(b=>b.addEventListener('click',()=>deleteStaff(b.dataset.id)));
}
function openStaffEdit(id){
  const s=staff.find(x=>x.id===id); if(!s) return;
  document.getElementById('es_id').value=id;
  document.getElementById('es_name').value=s.name;
  document.getElementById('es_dept').value=s.dept;
  document.getElementById('es_role').value=s.role||'';
  document.getElementById('popupStaff').style.display='flex';
}
function deleteStaff(id){
  const s=staff.find(x=>x.id===id); if(!s) return;
  showConfirm('ลบพนักงาน',`ลบ '${s.name}' ออกจากระบบ? ประวัติคะแนนและงานเดิมจะยังคงอยู่`,'ลบ','btn-danger btn-sm',()=>{
    db.collection('staff').doc(id).delete().then(()=>toast(`ลบ '${s.name}' เรียบร้อย`,'warn'));
  });
}

/* ════════════════ REALTIME ════════════════ */
function listenRealtime(){
  db.collection('tasks').onSnapshot(snap=>{
    tasks=[]; snap.forEach(d=>tasks.push({id:d.id,...d.data()}));
    refreshActiveView();
    document.getElementById('connDot').className='badge-dot';
    document.getElementById('connText').textContent='เชื่อมต่อแล้ว';
  },()=>{
    document.getElementById('connDot').className='badge-dot warn';
    document.getElementById('connText').textContent='ออฟไลน์';
  });
  db.collection('staff').onSnapshot(snap=>{
    staff=[]; snap.forEach(d=>staff.push({id:d.id,...d.data()}));
    fillDeptSelectors(); fillStaffSelectors();
    refreshActiveView();
  });
  db.collection('scorelog').onSnapshot(snap=>{
    scoreLog=[]; snap.forEach(d=>scoreLog.push({id:d.id,...d.data()}));
    refreshActiveView();
  });
}
function refreshActiveView(){
  const active=document.querySelector('.section.active');
  if(!active) return;
  const id=active.id.replace('view-','');
  if(id==='dashboard') renderDashboard();
  if(id==='board') renderBoard();
  if(id==='overdue') renderOverdue();
  if(id==='leaderboard') renderLeaderboard();
  if(id==='scorelog') renderScoreLog();
  if(id==='staff') renderStaffTable();
}

/* ════════════════ PWA SETUP ════════════════ */
function setupPWA(){
  // Register the real service worker file (sw.js) — enables installability + offline cache
  if('serviceWorker' in navigator){
    navigator.serviceWorker.register('sw.js').catch(()=>{ /* ไม่รองรับใน context นี้ ข้ามไป */ });
  }

  // Install button logic
  let deferredPrompt=null;
  const btn=document.getElementById('btnInstallApp');
  window.addEventListener('beforeinstallprompt',(e)=>{
    e.preventDefault();
    deferredPrompt=e;
    btn.style.display='flex';
  });
  btn.addEventListener('click', async ()=>{
    if(!deferredPrompt){
      toast('เบราว์เซอร์นี้อาจไม่รองรับการติดตั้ง หรือเว็บต้องเปิดผ่าน https/localhost','warn');
      return;
    }
    deferredPrompt.prompt();
    const choice=await deferredPrompt.userChoice;
    if(choice.outcome==='accepted') toast('ติดตั้งแอปเรียบร้อย ✔','success');
    deferredPrompt=null;
    btn.style.display='none';
  });
  window.addEventListener('appinstalled', ()=>{
    btn.style.display='none';
    toast('ติดตั้งแอปลงเครื่องเรียบร้อยแล้ว 📲','success');
  });
}

/* ════════════════ INIT ════════════════ */
document.addEventListener('DOMContentLoaded',()=>{
  setupPWA();
  setupNav();
  document.getElementById('t_due').value=todayStr();

  document.getElementById('btnSaveTask').onclick=saveTask;
  document.getElementById('btnClearTask').onclick=()=>{ ['t_title','t_desc'].forEach(id=>document.getElementById(id).value=''); };

  document.getElementById('boardSearch').addEventListener('input',renderBoard);
  document.getElementById('boardFilterDept').addEventListener('change',renderBoard);
  document.getElementById('boardFilterPriority').addEventListener('change',renderBoard);

  document.getElementById('btnCloseTask').onclick=()=>document.getElementById('popupTask').style.display='none';
  document.getElementById('popupTask').onclick=function(e){ if(e.target===this) this.style.display='none'; };
  document.getElementById('btnSaveTaskDetail').onclick=saveTaskDetail;
  document.getElementById('btnDeleteTask').onclick=deleteTask;

  document.getElementById('btnModeGive').onclick=()=>switchScoreMode('give');
  document.getElementById('btnModeTake').onclick=()=>switchScoreMode('take');
  document.getElementById('btnSubmitScore').onclick=submitScore;

  document.getElementById('lbDeptFilter').addEventListener('change',renderLeaderboard);
  document.getElementById('lbPeriod').addEventListener('change',renderLeaderboard);

  document.getElementById('logSearch').addEventListener('input',renderScoreLog);
  document.getElementById('logTypeFilter').addEventListener('change',renderScoreLog);

  document.getElementById('btnAddStaff').onclick=addStaff;
  document.getElementById('btnCloseStaffEdit').onclick=()=>document.getElementById('popupStaff').style.display='none';
  document.getElementById('popupStaff').onclick=function(e){ if(e.target===this) this.style.display='none'; };
  document.getElementById('btnSaveStaffEdit').onclick=()=>{
    const id=document.getElementById('es_id').value;
    db.collection('staff').doc(id).update({
      name:document.getElementById('es_name').value.trim(),
      dept:document.getElementById('es_dept').value.trim(),
      role:document.getElementById('es_role').value.trim()
    }).then(()=>{ document.getElementById('popupStaff').style.display='none'; toast('แก้ไขเรียบร้อย ✔','success'); });
  };

  listenRealtime();
});
</script>
</body>
</html>
