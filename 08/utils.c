#include <Python.h>
#include <stdbool.h>

#define MAX_KEY 256
#define MAX_VAL 128

#define MAX_KEYS 100000
#define MAX_RET 5000000

typedef enum JsonTokenType
{
    None = 0,
    Number,
    Float,
    String,
    Bool
} t_jtype;

typedef struct JsonRecord
{
    char	key[MAX_KEY];
    t_jtype	type;
    char	str[MAX_VAL];
    long	num;
    bool	logic;
    double	numf;
} t_jrec;

size_t countSymbol(char c, char*str)
{
    size_t	n;
    bool	quote = false;

    for(size_t i = n = 0; str[i] != '\0'; ++i)
    {
        if(str[i] == '"')
        {
            quote = !quote;
        }
        else if(str[i] == c && !quote)
        {
            ++n;
        }
    }
    return n;
}


size_t parseJson(char *str, t_jrec *data, size_t nrec)
{
    size_t n = 0;
    size_t j;

    for(size_t i = 0; str[i] != '\0'; )
    {
        if(str[i] == '"')
        {
            data[n].type = None;
            ++i;
            for(j = 0; str[i] != '"' && str[i] != '\0'; ++i)
            {
                data[n].key[j++] = str[i];
            }
            data[n].key[j++] = '\0';
            while(str[i] != ':' && str[i] != '\0')
            {
                ++i;
            }
            ++i;
            while(isspace(str[i]) && str[i] != '\0')
            {
                ++i;
            }
            if(str[i] == '[' || str[i] == ']' || str[i] == '{' ||
               str[i] == '}' || str[i] == ',' || str[i] == '\0')
            {
                continue;
            }
            if(str[i] == '"')
            {
                data[n].type = String;
                i++;
                for(j = 0; str[i] != '"' && str[i] != '\0'; ++i)
                {
                    data[n].str[j++] = str[i];
                }
                ++i;
                data[n].str[j++] = '\0';
            }
            else if(isdigit(str[i]) || str[i] == '-')
            {
                j = 1;
                while(isdigit(str[i+j]) && str[i] != '\0')
                {
                    ++j;
                }
                if(str[i+j] == '.')
                {
                    data[n].type = Float;
                    /*
                    ++j;
                    while(isdigit(str[i+j]) && str[i] != '\0')
                    {
                        ++j;
                    }
                    strncpy(data[n].str, str + i, j);
                    */
                    sscanf(str + i, "%lf", &data[n].numf);
                }
                else
                {
                    data[n].type = Number;
                    data[n].num = atol(str+i*sizeof(char));
                }
                ++i;
                while((isdigit(str[i]) || str[i]=='.') && str[i] != '\0')
                {
                    ++i;
                }
            }
            else if(strncmp(str+i, "true", 4) == 0 || strncmp(str+i, "false", 5) == 0)
            {
                data[n].type = Bool;
                data[n].logic = strncmp(str + i, "true", 4) == 0 ? true : false;
            }
            if(data[n].type != None)
            {
                n++;
            }
        }
        else
        {
            i++;
        }
    }
    return n;
}

static PyObject* utils_loads(PyObject *self, PyObject *args)
{
    char *command;
    static t_jrec D[MAX_KEYS];
    size_t nrec;
    size_t recs;
    PyObject *ret = PyDict_New();
    PyObject *o = NULL;

    if (!PyArg_ParseTuple(args, "s", &command))
    {
        printf("ERROR: Can't loads() data\n");
        return NULL;
    }
    nrec = countSymbol(':', command);
    recs = parseJson(command, D, nrec);
    for(size_t i = 0; i < recs; i++)
    {
        switch(D[i].type)
        {
            case Number:
                o = PyLong_FromLong(D[i].num);
                break;
            case Float:
                o = PyFloat_FromDouble(D[i].numf);
                break;
            case String:
                o = PyUnicode_FromString(D[i].str);
                break;
            case Bool:
                o = D[i].logic ? Py_True : Py_False;
                break;
            default:
                o = NULL;
        }
        PyDict_SetItem(ret, PyUnicode_FromString(D[i].key), o);
    }

    return ret;
}

static PyObject* utils_dumps(PyObject *self, PyObject *args)
{
    PyObject *dict;
    Py_ssize_t len;
    PyObject *key = NULL, *value = NULL;
    Py_ssize_t pos = 0;
    char ret[MAX_RET];
    size_t retpos = 0;
    size_t spos;
    char *s;
    char buf[MAX_VAL];
    bool is_str;
    PyObject *o;

    if (!PyArg_ParseTuple(args, "O", &dict))
    {
        printf("ERROR: Can't get data for dumps()\n");
        return NULL;
    }
    len = PyDict_Size(dict);
    ret[retpos++] = '{';
    while(PyDict_Next((PyObject *) dict, &pos, &key, &value))
    {
        ret[retpos++] = '"';
        s = PyBytes_AsString(PyUnicode_AsUTF8String(key));
        spos = 0;
        while(s[spos] != '\0')
        {
            ret[retpos++] = s[spos++];
        }
        ret[retpos++] = '"';
        ret[retpos++] = ':';
        ret[retpos++] = ' ';
        is_str = false;
        if(PyLong_CheckExact(value))
        {
            sprintf(buf, "%ld", PyLong_AsLong(value));
            s = buf;
        }
        else if(PyFloat_CheckExact(value))
        {
            sprintf(buf, "%lf", PyFloat_AsDouble(value));
            s = buf;
        }
        else if(PyBool_Check(value))
        {
            if(PyObject_IsTrue(value))
            {
                s = "true";
            }
            else {
                s = "false";
            }
        }
        else {
            o = PyUnicode_AsUTF8String(value);
            if(o != NULL)
            {
                s = PyBytes_AsString(o);
            }
            is_str = true;
        }
        spos = 0;
        if(is_str)
        {
            ret[retpos++] = '"';
        }
        while(s[spos] != '\0')
        {
            ret[retpos++] = s[spos++];
        }
        if(is_str)
        {
            ret[retpos++] = '"';
        }
        if(pos < len)
        {
            ret[retpos++]=',';
            ret[retpos++]=' ';
        }
    }
    ret[retpos++] = '}';
    ret[retpos++] = '\0';

    return Py_BuildValue("s", ret);
}

static PyMethodDef methods[] = {
        {"loads", utils_loads, METH_VARARGS, "Build dict data from json string"},
        {"dumps", utils_dumps, METH_VARARGS, "Build json string from dict data"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef utilsmodule = {
        PyModuleDef_HEAD_INIT, "utils_sum",
        NULL, -1, methods
};

PyMODINIT_FUNC PyInit_utils(void)
{
    return PyModule_Create(&utilsmodule);
}