import socket


class SimKnx:

    def __init__(self, host="localhost", port=1234):
        """ Constructor with default parameters """
        self.__SimKnx_host = host
        self.__SimKnx_port = port

    def setBoolObject(self, objectNumber, value: bool):
        """ Sets a value to a boolean object """
        request = 'set {} {}'.format(objectNumber, int(value))
        self.__setObject(request)

    def setDimmerObject(self, objectNumber, direction: bool, value: int):
        """ Sets a dimmer object """
        request = 'set {} {} {}'.format(objectNumber, int(direction), value)
        self.__setObject(request)

    def setintegerObject(self, objectNumber, value: int):
        """ Sets a value to an integer object """
        request = 'set {} {}'.format(objectNumber, value)
        self.__setObject(request)

    def __setObject(self, request):
        """ Send UDP request to set an object """
        # Create UDP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Send the message
        sock.sendto(request.encode("utf-8"), (self.__SimKnx_host, self.__SimKnx_port))

        sock.close()

    def getObjectType(self, objectNumber: int):
        """ Get the type for a SIM-KNX object """
        request = "type {}".format(objectNumber)
        return int(self.__getResponse(request))

    def getObject(self, objectNumber: int):
        """ Get the value for the specified object """
        request = "get {}".format(objectNumber)
        return int(self.__getResponse(request))

    def __getResponse(self, request):
        """ Send the request and get the response back"""

        # Create socket and bind it to localhost for a response
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(('', 4321))

        # Send the message and ask for the object type
        sock.sendto(request.encode("utf-8"), (self.__SimKnx_host, self.__SimKnx_port))
        data = sock.recvfrom(10)
        sock.close()

        return data[0]
