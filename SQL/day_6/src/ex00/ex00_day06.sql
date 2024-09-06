create table person_discounts(
    id bigint NOT NULL,
    person_id bigint NOT NULL,
    pizzeria_id bigint NOT NULL,
    discount numeric,
    PRIMARY KEY (id),
    FOREIGN KEY (person_id) REFERENCES person(id),
    FOREIGN KEY (pizzeria_id) REFERENCES pizzeria(id)
)