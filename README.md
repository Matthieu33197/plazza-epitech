<div id="top"></div>
<br />
<div align="center">
  <a href="https://github.com/EpitechPromo2025/B-CCP-400-PAR-4-1-theplazza-martin.leblancs">
    <img src="https://res.cloudinary.com/tkwy-prod-eu/image/upload/c_thumb,h_120,w_176/f_auto/q_auto/dpr_1.0/v1633694819/static-takeaway-com/images/restaurants/fr/ONN7Q17N/logo_465x320" alt="Logo" width="200" height="150">
  </a>

  <h3 align="center">ThePlazza</h3>

  <p align="center">
    Who said anything about pizzas ?
    <br />
  </p>
</div>



<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#documentation">Documentation</a></li>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>

## About The Project

<div align="center">
    <img src="https://clipart.world/wp-content/uploads/2021/01/Pizza-Restaurant-clipart-transparent.png" alt="Logo" width="400" height="366">
</div>


The purpose of this project is to make you realize a simulation of a pizzeria, which is composed of the
reception that accepts new commands, of several kitchens, themselves with several cooks, themselves
cooking several pizzas.
You will learn to deal with various problems, including load balancing, process and thread synchronization
and communication

the project is built using threads and child processes

### Built With

* [C++](https://en.cppreference.com/w/)

## Usage

  ```sh
  - make re
  - ./plazza [multiplier pizza cook time] [cooks per kitchen] [time to replace ingredients]
  ```

• The first parameter is a multiplier for the cooking time of the pizzas. It is used to examine your program
more easily, so it must INEVITABLY be implemented. Otherwise it will not be possible to grade you.
Moreover this parameter MUST be able to accept numbers with value in between 0 to 1 to obtain a
divisor of the pizzas cooking time. . . Cooking time is detailed later.

• The second parameter is the number of cooks per kitchen. Cook definition is detailed later.

• The third parameter is the time in milliseconds, used by the kitchen stock to replace ingredients. Ingredient definition is detailed later.

Informations:

```sh
  Use -h option to see more informations [./plazza -h]
```

Example:

```sh
  ./plazza 2 5 2000
```

<p align="right">(<a href="#top">back to top</a>)</p>
