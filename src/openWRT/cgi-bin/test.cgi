
import cgi
fs = cgi.FieldStorage()

print "Content-type: text/plain\n"
for key in fs.keys():
    print "%s = %s" % (key, fs[key].value)