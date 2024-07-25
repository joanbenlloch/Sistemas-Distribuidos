import sys
import logging
import pymysql
import json

rds_host = "54.227.14.168"

username = "admin"
password = "password"
dbname = "pr3_twitter"



def lambda_handler(event , context):
    nombre=event["queryStringParameters"]["nombre"];
    pas=event["queryStringParameters"]["passw"];
    #recu=event["queryStringParameters"]["recu"];

    userId=""
    result="";
    redirectPage="";
    print(nombre);
    print(pas);
    #print(recu);
    
  
    
    try:
        conn = pymysql.connect(rds_host, user=username, passwd=password, db=dbname, connect_timeout=10, port=3306)
        with conn.cursor() as cur:

            cur.execute("SELECT * FROM usuarios WHERE nombre=%s", (nombre))
            result1 = cur.fetchone()

            
            cur.execute("SELECT * FROM usuarios WHERE contraseña=%s AND nombre=%s", (pas, nombre))
            result2 = cur.fetchone()

            if not result1:
                result = "Error1"
                cur.close();
            elif not result2:
                result= "Error2"
                cur.close();
            else:
                cur.execute("select id from usuarios where nombre=%s",(nombre))
                userId = cur.fetchone()[0];
                cur.execute("select pagename from webpages where type='perfil' ");
                redirectPage=cur.fetchone()[0];
                result = "operacion correcta"
                cur.close();
    except pymysql.MySQLError as e:    
        print (e)
    conn.close();
    return {
        'statusCode': 200,
        'headers': { 'Access-Control-Allow-Origin' : '*' },
        'body' : json.dumps( { 'res': result, 'redirect': redirectPage, 'uname': nombre, 'id' : userId} )
    }
#          