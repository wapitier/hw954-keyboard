import sys
from pathlib import Path
p=Path(sys.argv[1]); s=p.read_text()
messages=["Stopping peripheral scanning", "Initiating new connection", "Scanning successfully started", "Scanning already running", "All devices are connected, scanning is unnecessary", "Not scanning, we're disabled", "[SUBSCRIBED]", "[UNSUBSCRIBED]", "Found the split service", "Found split service"]
for msg in messages:
    old='LOG_DBG("'+msg+'")'; new='LOG_INF("RFTRACE '+msg+'")'
    if old not in s and new not in s: raise SystemExit('Missing trace point: '+msg)
    s=s.replace(old,new)
p.write_text(s)
