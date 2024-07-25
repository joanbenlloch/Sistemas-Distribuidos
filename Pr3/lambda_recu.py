import sys
import logging
import pymysql
import json

rds_host = "54.227.14.168"

username = "admin"
password = "password"
dbname = "pr3_twitter"



def lambda_handler(event , context):
    recu=event["queryStringParameters"]["recu"]
    nombre=event["queryStringParameters"]["nombre"]

    result=""
    print(recu)
    print(nombre)
        
    try:
        conn = pymysql.connect(rds_host, user=username, passwd=password, db=dbname, connect_timeout=10, port=3306)
        with conn.cursor() as cur:

            cur.execute("SELECT contraseña FROM usuarios WHERE recu=%s AND nombre=%s ", (recu,nombre))
            result = cur.fetchone()

            if not result:
                result = "Error, frase de recuperación incorrecta"
            else:
                
                cur.close()
    except pymysql.MySQLError as e:    
        print (e)
    conn.close()
    return {
        'statusCode': 200,
        'headers': { 'Access-Control-Allow-Origin' : '*' },
        'body' : json.dumps( { 'passw': result} )
    }