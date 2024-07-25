import sys
import logging
import pymysql
import json
import re

rds_host = "54.227.14.168"

username = "admin"
password ="password"
dbname = "pr3_twitter"



def lambda_handler(event , context):
    nombre=event["queryStringParameters"]["nombre"];
    email=event["queryStringParameters"]["email"];
    passw=event["queryStringParameters"]["passw"];
    recu=event["queryStringParameters"]["recu"];
    bio=event["queryStringParameters"]["bio"];

    result="";
    redirectPage="";
    print(nombre);
    print(email);
    print(passw);
    print(recu);
    print(bio);
    
  
    
    try:
        conn = pymysql.connect(rds_host, user=username, passwd=password, db=dbname, connect_timeout=10, port=3306)
        with conn.cursor() as cur:

            cur.execute("SELECT * FROM usuarios WHERE nombre=%s", (nombre))
            result1 = cur.fetchone()

            pattern = r'^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$'
            cur.execute("SELECT * FROM usuarios WHERE correo REGEXP %s", (pattern))
            result2 = cur.fetchone()

            if result1 or (nombre == ""):
                result = "Error1"
            elif not re.match(pattern,email):
                result= "Error2"
            else:
                cur.execute("insert into usuarios (nombre, correo, contraseña, recu, biografia) values ('" +nombre +"','"+email+"','" +passw+ "','" + recu+"','"+bio+ "')");
                conn.commit();
                cur.execute("select pagename from webpages where type='inicio' ");
                redirectPage=cur.fetchone()[0];
                result = "operacion correcta"
                cur.close();
    except pymysql.MySQLError as e:    
        print (e)
    conn.close();
    return {
        'statusCode': 200,
        'headers': { 'Access-Control-Allow-Origin' : '*' },
        'body' : json.dumps( { 'res': str(result), 'redirect': redirectPage} )
    }
#     