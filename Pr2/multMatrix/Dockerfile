
FROM ubuntu:20.04
RUN apt-get update
RUN apt-get install -y software-properties-common
RUN mkdir /Ejecutables
RUN mkdir /Compartida
EXPOSE 30001
COPY mainServidorMM /Ejecutables
RUN chmod +x /Ejecutables/mainServidorMM
CMD /Ejecutables/mainServidorMM
