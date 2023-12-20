import json
import ujson
import simplejson as cjson
import time
import utils
LOOP=10

files=['testfl.json', 'bool.json', 'dummy.json', 'file_size2.json', 'file_perm.json', 'in.json', 'file_size.json']
def main():
    datas = [None] * len(files)
    json_doc = [None] * len(files)
    cjson_doc = [None] * len(files)
    ujson_doc = [None] * len(files)
    utils_doc = [None] * len(files)
    i=0

    for filename in files:
        with open(filename, 'r') as file:
            datas[i] = file.read()
            file.close()
            i += 1

    start_ts = time.time()
    for i in range(LOOP):
        j = 0
        for data in datas:
            json_doc[j] = json.loads(data)
            j += 1
    end_ts = time.time()
    print(f" json.loads exec time: {end_ts-start_ts}")
    start_ts = time.time()
    for i in range(LOOP):
        for json_d in json_doc:
            json_str = json.dumps(json_d)
    end_ts = time.time()
    print(f" json.dumps exec time: {end_ts-start_ts}\n")

    start_ts = time.time()
    for i in range(LOOP):
        j = 0
        for data in datas:
            cjson_doc[j] = cjson.loads(data)
            j += 1
    end_ts = time.time()
    print(f"cjson.loads exec time: {end_ts-start_ts}")
    start_ts = time.time()
    for i in range(LOOP):
        for cjson_d in cjson_doc:
            cjson_str = json.dumps(cjson_d)
    end_ts = time.time()
    print(f"cjson.dumps exec time: {end_ts-start_ts}\n")

    start_ts = time.time()
    for i in range(LOOP):
        j = 0
        for data in datas:
            ujson_doc[j] = ujson.loads(data)
            j += 1
    end_ts = time.time()
    print(f"ujson.loads exec time: {end_ts-start_ts}")
    start_ts = time.time()
    for i in range(LOOP):
        for ujson_d in ujson_doc:
            ujson_str = json.dumps(ujson_d)
    end_ts = time.time()
    print(f"ujson.dumps exec time: {end_ts-start_ts}\n")

    start_ts = time.time()
    for i in range(LOOP):
        j = 0
        for data in datas:
            utils_doc[j] = utils.loads(data)
            j += 1
    end_ts = time.time()
    print(f"utils.loads exec time: {end_ts-start_ts}")
    start_ts = time.time()
    for i in range(LOOP):
        for utils_d in utils_doc:
            utils_str = utils.dumps(utils_d)
    end_ts = time.time()
    print(f"utils.dumps exec time: {end_ts-start_ts}\n")

    print("Test loads() == json.loads() == ujson_loads() == cjson.loads()")
    for i in range(len(json_doc)):
        assert json_doc[i] == ujson_doc[i] == cjson_doc[i] == utils_doc[i]

    print(f"Test x == dumps(loads(x)) for {files}")
    for utils_d in utils_doc:
        utils_str = utils.dumps(utils_d)
        assert utils_str == utils.dumps(utils.loads(utils_str))

if __name__ == "__main__":
    main()