import csv
import random
import time
import faker

fake = faker.Faker()

def random_date(start, end):
    stime = time.mktime(time.strptime(start, '%Y-%m-%d'))
    etime = time.mktime(time.strptime(end, '%Y-%m-%d'))
    ptime = stime + random.random() * (etime - stime)
    return time.strftime('%a %b %d %H:%M:%S +0000 %Y', time.localtime(ptime))

def random_university():
    universities = ['pucv_cl', 'udeconcepcion', 'userena']
    return random.choice(universities)

def random_user_id():
    return random.randint(100000000, 999999999999999999)

def random_user_name():
    return fake.user_name()

def random_number():
    return random.randint(0, 10000)

def create_csv(filename, rows):
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['University', 'User ID', 'User Name', 'Number Tweets', 'Friends Count', 'Followers Count', 'Created At'])
        for _ in range(rows):
            writer.writerow([random_university(), random_user_id(), random_user_name(), random_number(), random_number(), random_number(), random_date('2005-01-01', '2023-12-31')])

create_csv('universities_followers_random.csv', 21071)  # Create a CSV file with 21071 rows of random data
