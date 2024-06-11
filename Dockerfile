#mkdir my-python-app
#cd my-python-app

# app.py
#print("Hello, Docker!")

FROM python:3.9

ENV TESTSCORE=1

ADD . /app

WORKDIR /app

CMD ["python3"]

#docker build -t my-python-app .

#docker run --rm my-python-app