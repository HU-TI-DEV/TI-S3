## MongoDB

### Using a GUI

You will use MongoDB most likely from the command line or directly from your application. For demonstrator purposes it might be easy to us for example [Mongo Compass](https://www.mongodb.com/products/tools/compass). Do not forget to open your port 27017. My external port 27018 was port forwarded to MongoDB internally using the standard port 27017. Use login name and password for authentication. Now you can easily view databases and the data they contain.

###  Using the command line

First check if MongoDB is installed.

```bash
mongod --version
```

It was not. Install with Homebrew.

```bash
brew tap mongodb/brew
brew install mongodb-community
brew services start mongodb/brew/mongodb-community
```

Use the MongoDB shell to connect remotely to your database.

```bash
mongosh "mongodb://mongodb:<password>@9.163.104.14:27018/"
```

It connects and I have a shell test>. To list all the databases I use the following command inside the shell.

```bash
show dbs
```

Using a database.

```bash
use gomoku
```

I find one collection games when I do.

```bash
show collections
```