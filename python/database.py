datas = {
	"host" : "localhost",
	"port" : "3306",
	"type" : "mysql",
	"user" : "tama",
	"pass" : "#?XxWw03",
	"name" : "tamagotchi",
}

url = "%(type)s://%(user)s:%(pass)s@%(host)s:%(port)s/%(name)s" % datas
print url

from sqlalchemy import MetaData

metadata = MetaData(url)

from sqlalchemy.schema import Table
table = Table( "test", metadata, autoload=True)

from sqlalchemy.orm import scoped_session, sessionmaker, mapper
from sqlalchemy import create_engine

maker = sessionmaker(autoflush=True)
session = scoped_session(maker)
session.configure(bind=create_engine(url))

class MappedObject(object): pass
mapper(MappedObject, table)

r = session.query(MappedObject)
print r[0].nom

r[0].nom = 'totoro'
session.add(r[0]
session.commit()
