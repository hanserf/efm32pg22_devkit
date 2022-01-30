Docker Development

Verify your git setup:
As we are develop linux application on and partially developing in Linux and Windows,
make sure
core.eol is set to native and
core.autocrlf is set to true.

Collect submodules:
git submodule update --init --recursive

Get started :
create a file name .env
linux users :

CURRENT_USER=`whoami`
id ${CURRENT_USER}
In .env put :

UID=1000 # Or Whatever id returned
GID=1001 # for your user
Windows Users?

Build container
``
docker build container/. -t arm-dev
```

Start Interactive session using Docker Compose
```
docker-compose run --rm arm-dev
```

