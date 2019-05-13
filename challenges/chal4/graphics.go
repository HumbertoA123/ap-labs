package main

import (
    "github.com/g3n/engine/util/application"
    "github.com/g3n/engine/geometry"
    "github.com/g3n/engine/material"
    "github.com/g3n/engine/math32"
    "github.com/g3n/engine/graphic"
    "github.com/g3n/engine/light"
)

func main() {

    app, _ := application.Create(application.Options{
        Title:  "Hello G3N",
        Width:  800,
        Height: 600,
    })

    // Create a blue torus and add it to the scene
    geom := geometry.NewCube(100)
    geom2 := geometry.NewCube(100)

    mat := material.NewPhong(math32.NewColor("DarkBlue"))
    mat2 := material.NewPhong(math32.NewColor("Red"))

    torusMesh := graphic.NewMesh(geom, mat)
    cubeMesh2 := graphic.NewMesh(geom2, mat2)

    app.Scene().Add(torusMesh)
    app.Scene().Add(cubeMesh2)


    // Add lights to the scene
    ambientLight := light.NewAmbient(&math32.Color{1.0, 1.0, 1.0}, 0.8)
    app.Scene().Add(ambientLight)
    pointLight := light.NewPoint(&math32.Color{1, 1, 1}, 5.0)
    pointLight.SetPosition(1, 0, 2)
    app.Scene().Add(pointLight)

    // Add an axis helper to the scene
    axis := graphic.NewAxisHelper(0.5)
    app.Scene().Add(axis)

    app.CameraPersp().SetPosition(0, 0, 3)
    app.Run()
}