APCu PS Module
==============

This module uses the APCu allocator, but a separate APCu cache to store sessions.

NOTE: APCu will need to be configured with enough shared memory to store sessions, this is hugely dependant on your application.

Things To Do
============

Persist sessions to disk on shutdown
Add some ini configuration for session cache

How To
======

Simply call

```php
session_module_name("apcu");
```

Before

```php
session_start();
```

And you are ready to go !!
