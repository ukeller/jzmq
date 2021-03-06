jarfile = zmq.jar
jardir = $(datadir)/java

javac_stamp = javac_stamp
javah_stamp = javah_stamp

JZMQ_JAVA_FILES = \
	../java/org/zeromq/EmbeddedLibraryTools.java \
	../java/org/zeromq/ZAuth.java \
	../java/org/zeromq/ZContext.java \
	../java/org/zeromq/ZDispatcher.java \
	../java/org/zeromq/ZFrame.java \
	../java/org/zeromq/ZLoop.java \
	../java/org/zeromq/ZMQ.java \
	../java/org/zeromq/ZMQException.java \
	../java/org/zeromq/ZMQForwarder.java \
	../java/org/zeromq/ZMQQueue.java \
	../java/org/zeromq/ZMQStreamer.java \
	../java/org/zeromq/ZMsg.java \
	../java/org/zeromq/ZThread.java \
	../java/org/zeromq/Utils.java

JZMQ_CPP_FILES = \
	ZMQ.cpp \
	Context.cpp \
	Socket.cpp \
	KeyPair.cpp \
	Poller.cpp \
	Event.cpp \
	Utils.cpp \
	util.cpp

JZMQ_H_FILES = \
	org_zeromq_ZMQ.h \
	org_zeromq_ZMQ_Context.h \
	org_zeromq_ZMQ_Error.h \
	org_zeromq_ZMQ_Event.h \
	org_zeromq_ZMQ_PollItem.h \
	org_zeromq_ZMQ_Poller.h \
	org_zeromq_ZMQ_Socket.h \
	org_zeromq_ZMQ_KeyPair.h

JZMQ_HPP_FILES = \
	util.hpp

JZMQ_CLASS_FILES = org/zeromq/*.class

$(javac_stamp): $(JZMQ_JAVA_FILES)
	$(JAVAC) $(JAVACFLAGS) -d . $(JZMQ_JAVA_FILES)
	@touch $@

$(jarfile): $(javac_stamp)
	$(JAR) cf $(JARFLAGS) $@ $(JZMQ_CLASS_FILES)

jar_DATA = $(jarfile)

dist_noinst_JAVA = $(JZMQ_JAVA_FILES)

lib_LTLIBRARIES = libjzmq.la
libjzmq_la_SOURCES = $(JZMQ_CPP_FILES)

nodist_libjzmq_la_SOURCES = \
	$(JZMQ_H_FILES) \
	$(JZMQ_HPP_FILES)

libjzmq_la_CXXFLAGS = -Wall

if DISABLE_VERSION
libjzmq_la_LDFLAGS = -avoid-version
else
libjzmq_la_LDFLAGS = -version-info @JLTVER@
endif

BUILT_SOURCES = \
	$(JZMQ_H_FILES)

CLEANFILES = \
	$(JZMQ_H_FILES) \
	$(jarfile) \
	$(javac_stamp) \
	$(javah_stamp)

clean-local:
	rm -rf org

$(JZMQ_H_FILES): $(javah_stamp)
$(javah_stamp): $(javac_stamp)
	$(CLASSPATH_ENV) $(JAVAH) -jni -classpath . org.zeromq.ZMQ org.zeromq.Utils
	@touch $@

$(srcdir)/ZMQ.cpp: \
	$(JZMQ_H_FILES) \
	$(JZMQ_HPP_FILES)

$(srcdir)/Context.cpp: \
	org_zeromq_ZMQ_Context.h \
	$(JZMQ_HPP_FILES)

$(srcdir)/Socket.cpp: \
	org_zeromq_ZMQ_Socket.h \
	$(JZMQ_HPP_FILES)

$(srcdir)/KeyPair.cpp: \
	org_zeromq_ZMQ_KeyPair.h \
	$(JZMQ_HPP_FILES)

$(srcdir)/Poller.cpp: \
	org_zeromq_ZMQ_Poller.h \
	$(JZMQ_HPP_FILES)

$(srcdir)/util.cpp: \
	$(JZMQ_HPP_FILES)

dist-hook:
	-rm $(distdir)/*.h
