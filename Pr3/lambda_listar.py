import sys
import logging
import pymysql
import json

rds_host = "54.227.14.168"

username = "admin"
password ="password"
dbname = "pr3_twitter"

def lambda_handler(event , context):

  id_usuario=event["queryStringParameters"]["id_username"]

  conn = pymysql.connect(rds_host, user=username, passwd=password, db=dbname, connect_timeout=10, port=3306)

  with conn.cursor() as cur:
  #cur = conn.cursor()

    cur.execute("SELECT cuerpo FROM mensajes WHERE id_usuario=%s", (id_usuario))
    rows1 = cur.fetchall()
    messages = []
  
  
    for row1 in rows1:
      message = row1[0]
      messages.append(message)
      
      
    cur.execute("SELECT archivo FROM mensajes WHERE id_usuario=%s", (id_usuario))
    rows2 = cur.fetchall()
    archivos = []
  
  
    for row2 in rows2:
      archivo = row2[0]
      archivos.append(archivo)

    cur.close()
  conn.close()

  return {
        'statusCode': 200,
        'headers': { 'Access-Control-Allow-Origin' : '*' },
        'body' : json.dumps( { 'mensajes': messages, 'archivos': archivos} )
    }