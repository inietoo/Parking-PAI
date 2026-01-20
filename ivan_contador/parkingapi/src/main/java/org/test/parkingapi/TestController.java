package org.test.parkingapi;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
//anotacion para indicar que este codigo devuelve HTTP
@RestController
public class TestController {
    //GetMapping esta indicando que cuando llegue una peticion Get en la ruta /hello devolvera el mensaje de debajo
    @GetMapping("/hello")
    public String hello() {
        return "Hola desde la API del parking api";
    }
}
