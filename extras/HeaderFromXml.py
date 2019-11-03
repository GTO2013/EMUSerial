#Quick and Dirty way to convert the emu .xml file to a c file
import xml.etree.ElementTree as ET
import re
import os

pattern = re.compile("(version[0-9]_[0-999])\w+")

xmlfile = None
filterfile = None

files = [f for f in os.listdir('.') if os.path.isfile(f)]
for f in files:
    if f == "filter.txt":
        filterfile = f
    elif pattern.match(f):
        xmlfile = f
      
if xmlfile is None:
    print("No file found, must match version[0-9]_[0-999].xml")
else:
    print("Found file: " + xmlfile)
  
    root = ET.parse(xmlfile).getroot()

    f = open("../src/format/emuFormat.h", "w",encoding='utf-8')
    fStruct = open("../src/format/emuStruct.h", "w",encoding='utf-8')
    variables = None

    if filterfile != None:
        print("Found filter.txt...\n")
        print("Filter: ")
        filters = []
          
        with open("filter.txt", "r") as filestream:
            for line in filestream.readlines():
                if line[0] !='#':
                    for entry in line.split(','):
                        s = entry.strip()
                        if s != "":
                            print(s)
                            filters.append(s)
        print()               
        if len(filters) > 0:
            if filters[0].isnumeric():
                print("Using channel ID filter with {0} allowed channels...".format(len(filters)))
                variables = list(filter(lambda x: x.tag == "symbol" and x.get("group")!= "Debug" and x.get("channel") != None and x.get("channel") in filters, root.find('frameData/variables')))
            else:
                print("Using name filter with {0} allowed names...".format(len(filters)))
                variables = list(filter(lambda x: x.tag == "symbol" and x.get("group")!= "Debug" and x.get("channel") != None and x.get("name").lower() in filters, root.find('frameData/variables')))
        else:
            print("filter.txt is empty, not filtering...")
    else:
        print("filter.txt was not found, not filtering...")
        
    if variables == None:
        variables = list(filter(lambda x: x.tag == "symbol" and x.get("group")!= "Debug" and x.get("channel") != None, root.find('frameData/variables')))

    variables.sort(key=lambda x: int(x.get("channel")), reverse=False)
    count = len(variables)
    print("Found {0} variables ...".format(count))

    f.write("#ifndef EMU_FORMAT_H\n")
    f.write("#define EMU_FORMAT_H\n")
    
    fStruct.write("#ifndef EMU_STRUCT_H\n")
    fStruct.write("#define EMU_STRUCT_H\n")
    
    f.write("#define EMU_" + xmlfile[:-4].upper() + "\n\n")
    fStruct.write("#define EMU_" + xmlfile[:-4].upper() + "\n\n")

    #Start channels array
    f.write("const uint8_t channels[" + str(count) +"]={")
    for i in range(count):
        type_tag = variables[i]
        divider = type_tag.get("channel")
        f.write(str(divider))

        if i < count - 1:
            f.write(",")

    #Close brackets
    f.write("};\n")

    #Start divider
    f.write("const int16_t divider[" + str(count) + "]={")
    for i in range(count):
        type_tag = variables[i]
        divider = type_tag.get("divider")
        f.write(str(divider))

        if i < count - 1:
            f.write(",")

    #Close brackets
    f.write("};\n\n")

    #Start storage
    #This tells us how we have to treat the incoming values
    
    f.write("#define EMU_TYPE_UBYTE 0\n#define EMU_TYPE_SBYTE 1\n#define EMU_TYPE_WORD 2\n#define EMU_TYPE_SWORD 3\n")
    f.write("const uint8_t typeIncoming [" + str(count) + "]={")
    for i in range(count):
        type_tag = variables[i]
        storage = type_tag.get("storage")

        if storage == "word":
            f.write("EMU_TYPE_WORD")
        elif storage == "sword":
            f.write("EMU_TYPE_SWORD")
        elif storage == "ubyte":
            f.write("EMU_TYPE_UBYTE")
        elif storage == "sbyte":
            f.write("EMU_TYPE_SBYTE")

        if i < count - 1:
            f.write(",")

    #Close brackets
    f.write("};\n\n")
  
    #Actual struct for live values
    fStruct.write("struct emu_data_t {\n")

    for type_tag in variables:
        divider = type_tag.get("divider")
        storage = type_tag.get("storage")

        #byte or word
        if divider == "1":
            if storage == "word":
                fStruct.write("\tuint16_t ")
            elif storage == "sword":
                fStruct.write("\tint16_t ")
            elif storage == "ubyte":
                fStruct.write("\tuint8_t ")
            elif storage == "sbyte":
                fStruct.write("\tint8_t ")
        #float
        else:
            fStruct.write("\tfloat ")

        fStruct.write(type_tag.get("name") +  ";  //" +  type_tag.get("unit"))
        fStruct.write("\n")
            
    #Close brackets
    fStruct.write("};\n")

    #map channel to data array
    f.write("const void* channelMapping[" + str(count) + "]={")
    for i in range(count):
        type_tag = variables[i]
        name = "&emu_data." + type_tag.get("name")
        f.write(name)
        if i < count - 1:
            f.write(",")
            
    f.write("};\n")
    
    f.write("#endif")
    fStruct.write("#endif")
    
    f.close()
    fStruct.close()

    print("Complete!")
