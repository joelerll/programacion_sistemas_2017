## Ejecutar servidor

```sh
$ ./server 127.0.0.1 5008
```

## Ejecutar Cliente

```sh
$ ./client 127.0.0.1 5008 /home/joelerll joel
```

## Comando en cliente

```sh
$ get hola.png
```

## Resolver error conflito de puertos

```sh
$ fuser -k 6000/tcp
```

## Hacer
ps -aux | grep foooo
kill -15 30476
kill $(ps aux | grep 'servidor' | awk '{print $2}')
lsof -i | grep 834

