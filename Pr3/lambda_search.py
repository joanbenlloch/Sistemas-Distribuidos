import sys
import logging
import pymysql
import json

rds_host = "54.227.14.168"

username = "admin"
password ="password"
dbname = "pr3_twitter"

def lambda_handler(event , context):

  usuario=event["queryStringParameters"]["userSearch"]
  usuario = "%"+usuario+"%"

  conn = pymysql.connect(host=rds_host, user=username, passwd=password, database=dbname, connect_timeout=10, port=3306)

  cursor = conn.cursor()

  cursor.execute("SELECT id FROM usuarios WHERE nombre LIKE %s",(usuario))

  id_usuarios= cursor.fetchall()

  list_return = []
  list_return2 = []

  for id_user in id_usuarios:
    cursor.execute("SELECT nombre FROM usuarios WHERE id=%s", (id_user[0]))
    inner_list = []
    inner_list.append(cursor.fetchall()[0][0])
    cursor.execute("SELECT nombre FROM usuarios WHERE id=%s", (id_user[0]))
    inner_list2 = []
    inner_list2.append(cursor.fetchall()[0][0])
    cursor.execute("SELECT cuerpo FROM mensajes WHERE id_usuario=%s", (id_user[0]))
    rows = cursor.fetchall()
    cursor.execute("SELECT archivo FROM mensajes WHERE id_usuario=%s", (id_user[0]))
    rows2 = cursor.fetchall()
    for row in rows:
        inner_list.append(row[0])
        
    for row2 in rows2:
      inner_list2.append(row2[0])
      
    list_return.append(inner_list)
    list_return2.append(inner_list2)
 
    

  cursor.close()
  conn.close()

  return {
    'statusCode': 200,
    'headers': { 'Access-Control-Allow-Origin' : '*' },
    'body' : json.dumps( { 'lista': list_return, 'archivos': list_return2} ) 
    
  }