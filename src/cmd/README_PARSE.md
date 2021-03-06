# Parsing manual

## List of main commands
1) `add` - adds component to scene
2) `rm` - removes component from scene
3) `set` - sets some parameter given value
3) `ls` - lists info about scene/object

### Default values
In case some additional parameters are not specified, they would be set to this default values:
1) scalar - `0.0`
1) vector - `<0.0, 0.0, 0.0>`
1) matrix 3x3 - `[<0.0, 0.0, 0.0>, <0.0, 0.0, 0.0>, <0.0, 0.0, 0.0>]`
1) string - empty string, `""`
3) material - defaul PBR material. See `scn_material.h`

### Command `add`
You must specify type of component to add.
If component is `object` you can set any of this parameters:
1) `-v` - visibility. Should be valid string - "true" or "false"
1) `-n` - name. Should be valid string - name
1) `-p` - position. Should be valid vector
1) `-a` - axis. Should be valid matrix 3x3
1) `-m` - material. Should be valid string - name of material
1) `-g` - group. Should be valid string - name of group

#### `add plane`
No special arguments can be specified.

#### `add sphere`
1) `-r` - radius. Should be valid scalar

#### `add cylinder`
1) `-r` - radius. Should be valid scalar
1) `-l` - length. Should be valid scalar

#### `add cone`
1) `-r` - radius. Should be valid scalar
1) `-l` - length. Should be valid scalar

#### `add camera`
Cannot specify material, `-m` will give an error.
1) `-f` - field-of-view, FOV. Should be valid vector
//change this to object instead of array

#### `add light`
Cannot specify material, `-m` will give an error.
1) `-i` - intensity. Should be valid scalar
1) `-c` - color. Should be valid vector (values clamped 0..1)

#### `add copy`
Adds dynamic copy of object.
Cannot specify material, `-m` will give an error.
1) `-o` - Object-original.  Should be valid string - name of object to copy from.

#### `add group`
Cannot specify material, `-m` will give an error.

#### `add material`
Material is not an object, so non of previous object flags can be used.
1) `-m` - metalness. Should be valid scalar
2) `-r` - roughness. Should be be valid scalar
3) `-i` - ior. Should be valid scalar
3) `-t` - transparency. Should be valid scalar
3) `-a` - albedo. Should be valid vector (values clamped 0..1)
3) `-f` - f0. Should be valid vector (values clamped 0..1)
   //TODO add maps as textures
3) `-N` - mormal map. Should be valid texture name

#### `add texture`
// File can be only png image
1) `-t` - type. Should be one of strings "RGB8", "RGBA8" or "BW8"
2) `-f` - filename. Should be valid string.


### Command `rm`
Removes component from scene.
Be careful because it will remove all copies as well.
If object is group all it's children's copies will be deleted.
1) `-r` - remove recursively

### Command `set`
Sets property value to component.
Gets object by name as first parameter.
Uses flags from `add` to specify parameters.

Example 1: `set "my_sphere" -r 2.0 `

Example 2: `set "my_light" -i 10.0 `

// ```set texture -f "myfile.png"``` saves png file instead of loading it unlike ```add texture -f```

### `ls`
Lists chosen component info
Gets object by name as first parameter.
If no flag/argument specified then it lists info about whole scene

## Comments
You can comment only full line by starting it with `#`

## Examples
```
# This is comment

# Adding default material
add material pbr "my_material"

#Adding sphere to the origin with default material, index 8 and radius 3 named my_sphere
<<<<<<< HEAD
add object sphere -i8 -m"my_material" -r3.0 "my_sphere"
=======
add sphere "my_sphere" -r3.0
>>>>>>> 04b620ed443469cd16a4ff6214ee6675bbc7b680

#add works like this
add object sphere "my_sphere" -p<0, 0, 0>

#set works like this
set object sphere "my_sphere" -p<0, 0, 0>
```

P.S.

В течении add и set комманд мы пытаемся провернуть операцию с временным объектом
Если в течении парсинга происходят ошибки просто очищаем временный объект
Иначе копируем временный объект в постоянное хранилище