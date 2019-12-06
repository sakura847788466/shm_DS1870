const express = require('express')
const app = express()
var server = require('http').Server(app)
var path = require('path')

app.use(express.static(path.join(__dirname, '/module')))



server.listen(3001, () => {
  console.log('server start in port' + 3001)
})